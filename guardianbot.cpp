#include <eosiolib/eosio.hpp>
#include <eosiolib/fixed_bytes.hpp>

using namespace eosio;

/*
 * This contract has to relay canceldelay actions because on the minimum auth requirements of eosio::canceldelay
 */

namespace eosdac {
    class [[eosio::contract("guardianbot")]] guardiancontract : public contract {
    public:
        using contract::contract;

        ACTION cancel(permission_level canceling_auth, checksum256 trx_id){
            require_auth(canceling_auth.actor);

            // upgrade to active permission (needs to be given to this contract)
            action(permission_level{canceling_auth.actor, "active"_n},
                   "eosio"_n, "canceldelay"_n,
                   std::make_tuple(
                           canceling_auth,
                           trx_id
                   )).send();
        }
    };
}

EOSIO_DISPATCH( eosdac::guardiancontract,
(cancel)
)
