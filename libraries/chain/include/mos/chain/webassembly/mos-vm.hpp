#pragma once

#if defined(MOS_MOS_VM_RUNTIME_ENABLED) || defined(MOS_MOS_VM_JIT_RUNTIME_ENABLED)

#include <mos/chain/webassembly/common.hpp>
#include <mos/chain/webassembly/runtime_interface.hpp>
#include <mos/chain/exceptions.hpp>
#include <mos/chain/apply_context.hpp>
#include <softfloat_types.h>

//mos-vm includes
#include <mos/vm/backend.hpp>

// mos specific specializations
namespace mos { namespace vm {

   template<>
   struct wasm_type_converter<mos::chain::name> {
      static auto from_wasm(uint64_t val) {
         return mos::chain::name{val};
      }
      static auto to_wasm(mos::chain::name val) {
         return val.to_uint64_t();
      }
   };

   template<typename T>
   struct wasm_type_converter<T*> : linear_memory_access {
      auto from_wasm(void* val) {
         validate_ptr<T>(val, 1);
         return mos::vm::aligned_ptr_wrapper<T, alignof(T)>{val};
      }
   };

   template<>
   struct wasm_type_converter<char*> : linear_memory_access {
      void* to_wasm(char* val) {
         validate_ptr<char>(val, 1);
         return val;
      }
   };

   template<typename T>
   struct wasm_type_converter<T&> : linear_memory_access {
      auto from_wasm(uint32_t val) {
         MOS_VM_ASSERT( val != 0, wasm_memory_exception, "references cannot be created for null pointers" );
         void* ptr = get_ptr(val);
         validate_ptr<T>(ptr, 1);
         return mos::vm::aligned_ref_wrapper<T, alignof(T)>{ptr};
      }
   };

   template<typename T>
   struct wasm_type_converter<mos::chain::array_ptr<T>> : linear_memory_access {
      auto from_wasm(void* ptr, uint32_t size) {
         validate_ptr<T>(ptr, size);
         return aligned_array_wrapper<T, alignof(T)>(ptr, size);
      }
   };

   template<>
   struct wasm_type_converter<mos::chain::array_ptr<char>> : linear_memory_access {
      auto from_wasm(void* ptr, uint32_t size) {
         validate_ptr<char>(ptr, size);
         return mos::chain::array_ptr<char>((char*)ptr);
      }
      // memcpy/memmove
      auto from_wasm(void* ptr, mos::chain::array_ptr<const char> /*src*/, uint32_t size) {
         validate_ptr<char>(ptr, size);
         return mos::chain::array_ptr<char>((char*)ptr);
      }
      // memset
      auto from_wasm(void* ptr, int /*val*/, uint32_t size) {
         validate_ptr<char>(ptr, size);
         return mos::chain::array_ptr<char>((char*)ptr);
      }
   };

   template<>
   struct wasm_type_converter<mos::chain::array_ptr<const char>> : linear_memory_access {
      auto from_wasm(void* ptr, uint32_t size) {
         validate_ptr<char>(ptr, size);
         return mos::chain::array_ptr<const char>((char*)ptr);
      }
      // memcmp
      auto from_wasm(void* ptr, mos::chain::array_ptr<const char> /*src*/, uint32_t size) {
         validate_ptr<char>(ptr, size);
         return mos::chain::array_ptr<const char>((char*)ptr);
      }
   };

   template <typename Ctx>
   struct construct_derived<mos::chain::transaction_context, Ctx> {
      static auto &value(Ctx& ctx) { return ctx.trx_context; }
   };

   template <>
   struct construct_derived<mos::chain::apply_context, mos::chain::apply_context> {
      static auto &value(mos::chain::apply_context& ctx) { return ctx; }
   };

   template<>
   struct wasm_type_converter<mos::chain::null_terminated_ptr> : linear_memory_access {
      auto from_wasm(void* ptr) {
         validate_c_str(ptr);
         return mos::chain::null_terminated_ptr{ static_cast<char*>(ptr) };
      }
   };

}} // ns mos::vm

namespace mos { namespace chain { namespace webassembly { namespace mos_vm_runtime {

using namespace fc;
using namespace mos::vm;
using namespace mos::chain::webassembly::common;

template<typename Backend>
class mos_vm_runtime : public mos::chain::wasm_runtime_interface {
   public:
      mos_vm_runtime();
      bool inject_module(IR::Module&) override;
      std::unique_ptr<wasm_instantiated_module_interface> instantiate_module(const char* code_bytes, size_t code_size, std::vector<uint8_t>,
                                                                             const digest_type& code_hash, const uint8_t& vm_type, const uint8_t& vm_version) override;

      void immediately_exit_currently_running_module() override;

   private:
      // todo: managing this will get more complicated with sync calls;
      //       immediately_exit_currently_running_module() should probably
      //       move from wasm_runtime_interface to wasm_instantiated_module_interface.
      backend<apply_context, Backend>* _bkend = nullptr;  // non owning pointer to allow for immediate exit

   template<typename Impl>
   friend class mos_vm_instantiated_module;
};

} } } }// mos::chain::webassembly::wabt_runtime

#define __MOS_VM_INTRINSIC_NAME(LBL, SUF) LBL##SUF
#define _MOS_VM_INTRINSIC_NAME(LBL, SUF) __INTRINSIC_NAME(LBL, SUF)

#define _REGISTER_MOS_VM_INTRINSIC(CLS, MOD, METHOD, WASM_SIG, NAME, SIG) \
   mos::vm::registered_function<mos::chain::apply_context, CLS, &CLS::METHOD> _MOS_VM_INTRINSIC_NAME(__mos_vm_intrinsic_fn, __COUNTER__)(std::string(MOD), std::string(NAME));

#else

#define _REGISTER_MOS_VM_INTRINSIC(CLS, MOD, METHOD, WASM_SIG, NAME, SIG)

#endif
