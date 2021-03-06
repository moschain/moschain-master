#include <mos/chain/webassembly/mos-vm-oc/gs_seg_helpers.h>

#include <asm/prctl.h>
#include <sys/prctl.h>

int arch_prctl(int code, unsigned long* addr);

#define MOSVMOC_MEMORY_PTR_cb_ptr GS_PTR struct mos_vm_oc_control_block* const cb_ptr = ((GS_PTR struct mos_vm_oc_control_block* const)(MOS_VM_OC_CONTROL_BLOCK_OFFSET));

int32_t mos_vm_oc_grow_memory(int32_t grow, int32_t max) {
   MOSVMOC_MEMORY_PTR_cb_ptr;
   uint64_t previous_page_count = cb_ptr->current_linear_memory_pages;
   int32_t grow_amount = grow;
   uint64_t max_pages = max;
   if(grow == 0)
      return (int32_t)cb_ptr->current_linear_memory_pages;
   if(previous_page_count + grow_amount > max_pages)
      return (int32_t)-1;

   uint64_t current_gs;
   arch_prctl(ARCH_GET_GS, &current_gs);
   current_gs += grow_amount * MOS_VM_OC_MEMORY_STRIDE;
   arch_prctl(ARCH_SET_GS, (unsigned long*)current_gs);
   cb_ptr->current_linear_memory_pages += grow_amount;
   cb_ptr->first_invalid_memory_address += grow_amount*64*1024;

   if(grow_amount > 0)
      memset(cb_ptr->full_linear_memory_start + previous_page_count*64u*1024u, 0, grow_amount*64u*1024u);

   return (int32_t)previous_page_count;
}

sigjmp_buf* mos_vm_oc_get_jmp_buf() {
   MOSVMOC_MEMORY_PTR_cb_ptr;
   return cb_ptr->jmp;
}

void* mos_vm_oc_get_exception_ptr() {
   MOSVMOC_MEMORY_PTR_cb_ptr;
   return cb_ptr->eptr;
}

void* mos_vm_oc_get_bounce_buffer_list() {
   MOSVMOC_MEMORY_PTR_cb_ptr;
   return cb_ptr->bounce_buffers;
}