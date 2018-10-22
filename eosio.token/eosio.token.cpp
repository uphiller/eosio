/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */

#include "eosio.token.hpp"

namespace eosio {

void token::create( account_name issuer,
                    asset        maximum_supply )
{
    // action을 푸시한 게정이 _self(컨트랙트 계정) 인지 확인
    require_auth( _self );

    // 파라메터로 들어온 에셋에 대한 심볼 추출
    auto sym = maximum_supply.symbol;

    // 심볼이 올바른 심볼인지 확인 
    eosio_assert( sym.is_valid(), "invalid symbol name" );
    // Asset에 대한 내용이 올바른지 확인
    eosio_assert( maximum_supply.is_valid(), "invalid supply");
    // 최대 발행량이 0보다 큰지 확인
    eosio_assert( maximum_supply.amount > 0, "max-supply must be positive");

    // 기존의 stat table 읽기
    stats statstable( _self, sym.name() );

    // 동일한 심볼을 갖는 stst이 있는지 확인
    auto existing = statstable.find( sym.name() );
    eosio_assert( existing == statstable.end(), "token with symbol already exists" );

    // 새로운 stat정보 저장
    statstable.emplace( _self, [&]( auto& s ) {
       s.supply.symbol = maximum_supply.symbol;
       s.max_supply    = maximum_supply;
       s.issuer        = issuer;
    });
}


void token::issue( account_name to, asset quantity, string memo )
{
    // 심볼에 대한 체크
    auto sym = quantity.symbol;
    eosio_assert( sym.is_valid(), "invalid symbol name" );

    // 메모의 크기가 256 보다 작은지 확인
    eosio_assert( memo.size() <= 256, "memo has more than 256 bytes" );

    // 심볼을 스코프로 하여 테이블 로드
    auto sym_name = sym.name();
    stats statstable( _self, sym_name );
    auto existing = statstable.find( sym_name );

    // 해당 심볼을 갖는 stat정보가 있는지 확인
    eosio_assert( existing != statstable.end(), "token with symbol does not exist, create token before issue" );
    const auto& st = *existing;

    // action을 push한 게정이 해당 토큰의 발행자 인지 체크
    require_auth( st.issuer );
    // 발행하려는 토큰의 수량이 0보다 큰지 확인
    eosio_assert( quantity.is_valid(), "invalid quantity" );
    eosio_assert( quantity.amount > 0, "must issue positive quantity" );
    // 발행하려는 토큰의 심볼이 stat정보과 맞는지 확인
    eosio_assert( quantity.symbol == st.supply.symbol, "symbol precision mismatch" );
    // 발행했을때의 발행량이 최대 발행량을 넘지는 않는지 확인 
    eosio_assert( quantity.amount <= st.max_supply.amount - st.supply.amount, "quantity exceeds available supply");

    // 공급량 업데이트
    statstable.modify( st, 0, [&]( auto& s ) {
       s.supply += quantity;
    });
    // 발행권자 게좌에 발행한 금액 추가
    add_balance( st.issuer, quantity, st.issuer );

    // 만일 발행된 토큰을 받을 사람이 발행자가 아니라면, 토큰 전송 
    if( to != st.issuer ) {
       SEND_INLINE_ACTION( *this, transfer, {st.issuer,N(active)}, {st.issuer, to, quantity, memo} );
    }
}

void token::transfer( account_name from,
                      account_name to,
                      asset        quantity,
                      string       memo )
{
    // 자기자신에게 보내는 전송이면 assert
    eosio_assert( from != to, "cannot transfer to self" );
    // action을 push한 게정이 from인지 확인
    require_auth( from );

    // 받을 계정이 EOS네트워크에 존재하는 계정인지 확인
    eosio_assert( is_account( to ), "to account does not exist");
    auto sym = quantity.symbol.name();
    stats statstable( _self, sym );
    const auto& st = statstable.get( sym );

    // from과 to 계정에 action 내용 전파
    require_recipient( from );
    require_recipient( to );

    eosio_assert( quantity.is_valid(), "invalid quantity" );
    eosio_assert( quantity.amount > 0, "must transfer positive quantity" );
    eosio_assert( quantity.symbol == st.supply.symbol, "symbol precision mismatch" );
    eosio_assert( memo.size() <= 256, "memo has more than 256 bytes" );

    // from의 잔액에서 보내려는 양만큼 잔액을 감소시키고, 받는 가람 잔액을 증가시킴
    sub_balance( from, quantity );
    add_balance( to, quantity, from );
}

void token::sub_balance( account_name owner, asset value ) {
   accounts from_acnts( _self, owner );

   const auto& from = from_acnts.get( value.symbol.name(), "no balance object found" );
   eosio_assert( from.balance.amount >= value.amount, "overdrawn balance" );


   if( from.balance.amount == value.amount ) {
      from_acnts.erase( from );
   } else {
      from_acnts.modify( from, owner, [&]( auto& a ) {
          a.balance -= value;
      });
   }
}

void token::add_balance( account_name owner, asset value, account_name ram_payer )
{
   accounts to_acnts( _self, owner );
   auto to = to_acnts.find( value.symbol.name() );
   if( to == to_acnts.end() ) {
      to_acnts.emplace( ram_payer, [&]( auto& a ){
        a.balance = value;
      });
   } else {
      to_acnts.modify( to, 0, [&]( auto& a ) {
        a.balance += value;
      });
   }
}

} /// namespace eosio
