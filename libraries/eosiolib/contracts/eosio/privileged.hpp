#pragma once
#include "producer_schedule.hpp"
#include "system.hpp"
#include "../../core/eosio/crypto.hpp"
#include "../../core/eosio/name.hpp"
#include "../../core/eosio/serialize.hpp"
#include "../../core/eosio/shard.hpp"

namespace eosio {

   namespace internal_use_do_not_use {
      extern "C" {
         __attribute__((eosio_wasm_import))
         bool is_privileged( uint64_t account );

         __attribute__((eosio_wasm_import))
         void get_resource_limits( uint64_t account, int64_t* ram_bytes, int64_t* net_weight, int64_t* cpu_weight );

         __attribute__((eosio_wasm_import))
         void set_resource_limits( uint64_t account, int64_t ram_bytes, int64_t net_weight, int64_t cpu_weight );

         __attribute__((eosio_wasm_import))
         void set_privileged( uint64_t account, bool is_priv );

         __attribute__((eosio_wasm_import))
         void set_blockchain_parameters_packed( char* data, uint32_t datalen );

         __attribute__((eosio_wasm_import))
         uint32_t get_blockchain_parameters_packed( char* data, uint32_t datalen );

         __attribute((eosio_wasm_import))
         int64_t set_proposed_producers( char*, uint32_t );

         __attribute__((eosio_wasm_import))
         void preactivate_feature( const capi_checksum256* feature_digest );

         __attribute__((eosio_wasm_import))
         int64_t set_proposed_producers_ex( uint64_t producer_data_format, char *producer_data, uint32_t producer_data_size );

         __attribute__((eosio_wasm_import))
         int64_t register_shard_packed( const char* data, uint32_t datalen );

         __attribute__((eosio_wasm_import))
         uint32_t get_xshard_packed( const struct capi_checksum256* xsh_id, char* data, uint32_t datalen );
      }
   }

  /**
   *  @defgroup privileged Privileged
   *  @ingroup contracts
   *  @brief Defines C++ Privileged API
   */

   /**
    *  Tunable blockchain configuration that can be changed via consensus
    *  @ingroup privileged
    */
   struct blockchain_parameters {

      /**
      * The maximum net usage in instructions for a block
      * @brief the maximum net usage in instructions for a block
      */
      uint64_t max_block_net_usage;

      /**
      * The target percent (1% == 100, 100%= 10,000) of maximum net usage; exceeding this triggers congestion handling
      * @brief The target percent (1% == 100, 100%= 10,000) of maximum net usage; exceeding this triggers congestion handling
      */
      uint32_t target_block_net_usage_pct;

      /**
      * The maximum objectively measured net usage that the chain will allow regardless of account limits
      * @brief The maximum objectively measured net usage that the chain will allow regardless of account limits
      */
      uint32_t max_transaction_net_usage;

      /**
       * The base amount of net usage billed for a transaction to cover incidentals
       */
      uint32_t base_per_transaction_net_usage;

      /**
       * The amount of net usage leeway available whilst executing a transaction (still checks against new limits without leeway at the end of the transaction)
       * @brief The amount of net usage leeway available whilst executing a transaction  (still checks against new limits without leeway at the end of the transaction)
       */
      uint32_t net_usage_leeway;

      /**
      * The numerator for the discount on net usage of context-free data
      * @brief The numerator for the discount on net usage of context-free data
      */
      uint32_t context_free_discount_net_usage_num;

      /**
      * The denominator for the discount on net usage of context-free data
      * @brief The denominator for the discount on net usage of context-free data
      */
      uint32_t context_free_discount_net_usage_den;

      /**
      * The maximum billable cpu usage (in microseconds) for a block
      * @brief The maximum billable cpu usage (in microseconds) for a block
      */
      uint32_t max_block_cpu_usage;

      /**
      * The target percent (1% == 100, 100%= 10,000) of maximum cpu usage; exceeding this triggers congestion handling
      * @brief The target percent (1% == 100, 100%= 10,000) of maximum cpu usage; exceeding this triggers congestion handling
      */
      uint32_t target_block_cpu_usage_pct;

      /**
      * The maximum billable cpu usage (in microseconds) that the chain will allow regardless of account limits
      * @brief The maximum billable cpu usage (in microseconds) that the chain will allow regardless of account limits
      */
      uint32_t max_transaction_cpu_usage;

      /**
      * The minimum billable cpu usage (in microseconds) that the chain requires
      * @brief The minimum billable cpu usage (in microseconds) that the chain requires
      */
      uint32_t min_transaction_cpu_usage;

      /**
       * Maximum lifetime of a transacton
       * @brief Maximum lifetime of a transacton
       */
      uint32_t max_transaction_lifetime;

      /**
      * The number of seconds after the time a deferred transaction can first execute until it expires
      * @brief the number of seconds after the time a deferred transaction can first execute until it expires
      */
      uint32_t deferred_trx_expiration_window;


      /**
      * The maximum number of seconds that can be imposed as a delay requirement by authorization checks
      * @brief The maximum number of seconds that can be imposed as a delay requirement by authorization checks
      */
      uint32_t max_transaction_delay;

      /**
       * Maximum size of inline action
       * @brief Maximum size of inline action
       */
      uint32_t max_inline_action_size;

      /**
       * Maximum depth of inline action
       * @brief Maximum depth of inline action
       */
      uint16_t max_inline_action_depth;

      /**
       * Maximum authority depth
       * @brief Maximum authority depth
       */
      uint16_t max_authority_depth;


      EOSLIB_SERIALIZE( blockchain_parameters,
                        (max_block_net_usage)(target_block_net_usage_pct)
                        (max_transaction_net_usage)(base_per_transaction_net_usage)(net_usage_leeway)
                        (context_free_discount_net_usage_num)(context_free_discount_net_usage_den)

                        (max_block_cpu_usage)(target_block_cpu_usage_pct)
                        (max_transaction_cpu_usage)(min_transaction_cpu_usage)

                        (max_transaction_lifetime)(deferred_trx_expiration_window)(max_transaction_delay)
                        (max_inline_action_size)(max_inline_action_depth)(max_authority_depth)
      )
   };



   struct registered_shard {
      eosio::name          name;          //< name should not be changed within a chainbase modifier lambda
      uint8_t              shard_type     = (uint8_t)eosio::shard_type::normal;
      eosio::name          owner;
      bool                 enabled        = false;
      uint8_t              opts           = 0; ///< options

      EOSLIB_SERIALIZE(eosio::registered_shard, (name)(shard_type)(owner)(enabled)(opts))
   };

   using registered_shard_var = std::variant<registered_shard>;

   struct xshard
   {
      checksum256          xsh_id;
      uint32_t             trx_action_sequence;
      eosio::name          owner;
      eosio::name          from_shard;
      eosio::name          to_shard;
      eosio::name          contract;
      eosio::name          action_type;
      std::vector<char>    action_data;

      EOSLIB_SERIALIZE(eosio::xshard, (xsh_id)(owner)(from_shard)(to_shard)(contract)(action_type)(action_data))
   };

   /**
    *  Set the blockchain parameters
    *
    *  @ingroup privileged
    *  @param params - New blockchain parameters to set
    */
   void set_blockchain_parameters(const eosio::blockchain_parameters& params);

   /**
    *  Retrieve the blolckchain parameters
    *
    *  @ingroup privileged
    *  @param params - It will be replaced with the retrieved blockchain params
    */
   void get_blockchain_parameters(eosio::blockchain_parameters& params);

    /**
    *  Get the resource limits of an account
    *
    *  @ingroup privileged
    *  @param account - name of the account whose resource limit to get
    *  @param ram_bytes -  output to hold retrieved ram limit in absolute bytes
    *  @param net_weight - output to hold net limit
    *  @param cpu_weight - output to hold cpu limit
    */
   inline void get_resource_limits( name account, int64_t& ram_bytes, int64_t& net_weight, int64_t& cpu_weight ) {
      internal_use_do_not_use::get_resource_limits( account.value, &ram_bytes, &net_weight, &cpu_weight );
   }

   /**
    *  Set the resource limits of an account
    *
    *  @ingroup privileged
    *  @param account - name of the account whose resource limit to be set
    *  @param ram_bytes - ram limit in absolute bytes
    *  @param net_weight - fractionally proportionate net limit of available resources based on (weight / total_weight_of_all_accounts)
    *  @param cpu_weight - fractionally proportionate cpu limit of available resources based on (weight / total_weight_of_all_accounts)
    */
   inline void set_resource_limits( name account, int64_t ram_bytes, int64_t net_weight, int64_t cpu_weight ) {
      internal_use_do_not_use::set_resource_limits( account.value, ram_bytes, net_weight, cpu_weight );
   }

   /**
    *  Proposes a schedule change using the legacy producer key format
    *
    *  @ingroup privileged
    *  @note Once the block that contains the proposal becomes irreversible, the schedule is promoted to "pending" automatically. Once the block that promotes the schedule is irreversible, the schedule will become "active"
    *  @param producers - vector of producer keys
    *
    *  @return an optional value of the version of the new proposed schedule if successful
    */
   std::optional<uint64_t> set_proposed_producers( const std::vector<producer_key>& prods );

   /**
    *  Proposes a schedule change using the more flexible key format
    *
    *  @ingroup privileged
    *  @note Once the block that contains the proposal becomes irreversible, the schedule is promoted to "pending" automatically. Once the block that promotes the schedule is irreversible, the schedule will become "active"
    *  @param producers - vector of producer authorities
    *
    *  @return an optional value of the version of the new proposed schedule if successful
    */
   inline std::optional<uint64_t> set_proposed_producers( const std::vector<producer_authority>& prods ) {
      auto packed_prods = eosio::pack( prods );
      int64_t ret = internal_use_do_not_use::set_proposed_producers_ex(1, (char*)packed_prods.data(), packed_prods.size());
      if (ret >= 0)
        return static_cast<uint64_t>(ret);
      return {};
   }

   /**
    *  Check if an account is privileged
    *
    *  @ingroup privileged
    *  @param account - name of the account to be checked
    *  @return true if the account is privileged
    *  @return false if the account is not privileged
    */
   inline bool is_privileged( name account ) {
      return internal_use_do_not_use::is_privileged( account.value );
   }

   /**
    *  Set the privileged status of an account
    *
    *  @ingroup privileged
    *  @param account - name of the account whose privileged account to be set
    *  @param is_priv - privileged status
    */
   inline void set_privileged( name account, bool is_priv ) {
      internal_use_do_not_use::set_privileged( account.value, is_priv );
   }

   /**
    * Pre-activate protocol feature
    *
    * @ingroup privileged
    * @param feature_digest - digest of the protocol feature to pre-activate
    */
   inline void preactivate_feature( const checksum256& feature_digest ) {
      auto feature_digest_data = feature_digest.extract_as_byte_array();
      internal_use_do_not_use::preactivate_feature(
         reinterpret_cast<const internal_use_do_not_use::capi_checksum256*>( feature_digest_data.data() )
      );
   }

   /**
    * Register shard
    *
    * @ingroup privileged
    * @param shard - shard that we want to register.
    */
   inline int64_t register_shard(const registered_shard_var& shard ) {
      auto packed_shard = eosio::pack( shard );
      return internal_use_do_not_use::register_shard_packed( (char*)packed_shard.data(), packed_shard.size() );
   }

   /**
    * Retrieve the xshard info by xsh_id.
    * @ingroup privileged
    *
    * @param xsh_id - the input xshard id.
    * @param xsh - output xshard info.
    */
   void get_xshard( const checksum256& xsh_id, xshard& xsh );
}
