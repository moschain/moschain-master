#pragma once

namespace mos { namespace vm {

// create constexpr flags for whether the backend should obey alignment hints
#ifdef MOS_VM_ALIGN_MEMORY_OPS
   inline constexpr bool should_align_memory_ops = true;
#else
   inline constexpr bool should_align_memory_ops = false;
#endif


#ifdef MOS_VM_SOFTFLOAT
   inline constexpr bool use_softfloat = true;
#else
   inline constexpr bool use_softfloat = false;
#endif

#ifdef MOS_VM_FULL_DEBUG
   inline constexpr bool mos_vm_debug = true;
#else
   inline constexpr bool mos_vm_debug = false;
#endif

}} // namespace mos::vm
