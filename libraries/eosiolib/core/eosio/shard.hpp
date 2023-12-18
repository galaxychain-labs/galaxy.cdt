/**
 *  @file
 *  @copyright defined in eos/LICENSE
 */
#pragma once
#include <cstdint>

namespace eosio {
    enum class shard_type: uint8_t {
        normal      = 0,
        privacy     = 1
    };
}