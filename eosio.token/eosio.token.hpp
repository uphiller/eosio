/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>

#include <string>

namespace eosiosystem {
   class system_contract;
}

namespace eosio {

   using std::string;

   class token : public contract {
      public:
         token( account_name self ):contract(self){}
      
         // 새로운 토큰을 만드는 함수
         void create( account_name issuer,
                      asset        maximum_supply);

         // 만들어진 토큰에 대해서 발행을 하는 함수 
         void issue( account_name to, asset quantity, string memo );
         
         // from 계정이 가진 토큰을 to 에게 전송하는 함수
         void transfer( account_name from,
                        account_name to,
                        asset        quantity,
                        string       memo );
      
         // 해당 심볼을 가진 토큰의 발행량을 확인하는 함수
         inline asset get_supply( symbol_name sym )const;
         
         // owner가 가진 sym 심볼을 가진 토큰의 잔액을 확인하는 함수
         inline asset get_balance( account_name owner, symbol_name sym )const;

      private:
         // 계정별 잔액 정보를 저장하는 구조체
         /// @abi table accounts i64
         struct account {
            asset    balance;

            uint64_t primary_key()const { return balance.symbol.name(); }
            EOSLIB_SERIALIZE(account,(balance))

         };
         // 발행한 토큰의 상태 값
         /// @abi table stat i64
         struct stat {
            asset          supply;
            asset          max_supply;
            account_name   issuer;

            uint64_t primary_key()const { return supply.symbol.name(); }
            EOSLIB_SERIALIZE(stat,(supply)(max_supply)(issuer))

         };

         typedef eosio::multi_index<N(accounts), account> accounts;
         typedef eosio::multi_index<N(stat), stat> stats;
         
         // owner가 가진 토큰의 수량 감액 / 증액
         void sub_balance( account_name owner, asset value );
         void add_balance( account_name owner, asset value, account_name ram_payer );

      public:
         struct transfer_args {
            account_name  from;
            account_name  to;
            asset         quantity;
            string        memo;
         };
   };

   asset token::get_supply( symbol_name sym )const
   {
      stats statstable( _self, sym );
      const auto& st = statstable.get( sym );
      return st.supply;
   }

   asset token::get_balance( account_name owner, symbol_name sym )const
   {
      accounts accountstable( _self, owner );
      const auto& ac = accountstable.get( sym );
      return ac.balance;
   }

} /// namespace eosio
EOSIO_ABI( eosio::token, (create)(issue)(transfer) )
