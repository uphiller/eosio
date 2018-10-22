#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;

//EOSIO.CDT 1.3.1 버전에서는 에러가 발생합니다. 테이블 abi생성이 되지 앉아서 에러가 발생합니다
//https://github.com/EOSIO/eos/issues/6009
CONTRACT addressbook : public eosio::contract {

 public:
    using contract::contract;
 
    [[eosio::action]]
      void upsert(name user, std::string first_name, std::string last_name, std::string street, std::string city, std::string state) {
        require_auth( user );
        address_index addresses(_self, _self.value);
        auto iterator = addresses.find( user.value );
        if( iterator == addresses.end() )
        {
          addresses.emplace(user, [&]( auto& row ) {
          row.key = user.value;
          row.first_name = first_name;
          row.last_name = last_name;
          row.street = street;
          row.city = city;
          row.state = state;
          });
        }
        else {
          std::string changes;
          addresses.modify(iterator, user, [&]( auto& row ) {
            row.key = user.value;
            row.first_name = first_name;
            row.last_name = last_name;
            row.street = street;
            row.city = city;
            row.state = state;
          });
        }
      } 

    [[eosio::action]]
    void erase(name user){
        address_index addresses(_self, _self.value);
        auto iterator = addresses.find( user.value );
        eosio_assert(iterator != addresses.end(), "Record does not exist");
        addresses.erase(iterator);
    }

 private:
    struct [[eosio::table]] person {
          uint64_t key;
          std::string first_name;
          std::string last_name;
          std::string street;
          std::string city;
          std::string state;
          uint64_t primary_key() const { return key; }
      };
      typedef eosio::multi_index<"people"_n, person> address_index;

};

EOSIO_DISPATCH( addressbook, (upsert)(erase) )
