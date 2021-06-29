#include <mos/chain/webassembly/mos-vm-oc.hpp>
#include <mos/chain/wasm_mos_constraints.hpp>
#include <mos/chain/wasm_mos_injection.hpp>
#include <mos/chain/apply_context.hpp>
#include <mos/chain/exceptions.hpp>

#include <vector>
#include <iterator>

namespace mos { namespace chain { namespace webassembly { namespace mosvmoc {

class mosvmoc_instantiated_module : public wasm_instantiated_module_interface {
   public:
      mosvmoc_instantiated_module(const digest_type& code_hash, const uint8_t& vm_version, mosvmoc_runtime& wr) :
         _code_hash(code_hash),
         _vm_version(vm_version),
         _mosvmoc_runtime(wr)
      {

      }

      ~mosvmoc_instantiated_module() {
         _mosvmoc_runtime.cc.free_code(_code_hash, _vm_version);
      }

      void apply(apply_context& context) override {
         const code_descriptor* const cd = _mosvmoc_runtime.cc.get_descriptor_for_code_sync(_code_hash, _vm_version);
         MOS_ASSERT(cd, wasm_execution_error, "MOS VM OC instantiation failed");

         _mosvmoc_runtime.exec.execute(*cd, _mosvmoc_runtime.mem, context);
      }

      const digest_type              _code_hash;
      const uint8_t                  _vm_version;
      mosvmoc_runtime&               _mosvmoc_runtime;
};

mosvmoc_runtime::mosvmoc_runtime(const boost::filesystem::path data_dir, const mosvmoc::config& mosvmoc_config, const chainbase::database& db)
   : cc(data_dir, mosvmoc_config, db), exec(cc) {
}

mosvmoc_runtime::~mosvmoc_runtime() {
}

std::unique_ptr<wasm_instantiated_module_interface> mosvmoc_runtime::instantiate_module(const char* code_bytes, size_t code_size, std::vector<uint8_t> initial_memory,
                                                                                     const digest_type& code_hash, const uint8_t& vm_type, const uint8_t& vm_version) {

   return std::make_unique<mosvmoc_instantiated_module>(code_hash, vm_type, *this);
}

//never called. MOS VM OC overrides eosio_exit to its own implementation
void mosvmoc_runtime::immediately_exit_currently_running_module() {}

}}}}
