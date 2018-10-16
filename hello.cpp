#include <eosiolib/eosio.hpp>
using namespace eosio;

CONTRACT hello : public eosio::contract {
  public:
      using contract::contract;
 
      [[eosio::action]]
      void hi( name user ) {
         require_auth( user );
         print( "Hello, ", name{user} );
      }
};

EOSIO_DISPATCH( hello, (hi) )

