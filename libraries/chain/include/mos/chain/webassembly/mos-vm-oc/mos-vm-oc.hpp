#pragma once

#include <mos/chain/types.hpp>
#include <mos/chain/webassembly/mos-vm-oc/mos-vm-oc.h>

#include <exception>

#include <stdint.h>
#include <stddef.h>
#include <setjmp.h>

#include <vector>
#include <list>

namespace mos { namespace chain {

class apply_context;

namespace mosvmoc {

using control_block = mos_vm_oc_control_block;

struct no_offset{};
struct code_offset{ size_t offset; };    //relative to code_begin
struct intrinsic_ordinal{ size_t ordinal; };

using mosvmoc_optional_offset_or_import_t = fc::static_variant<no_offset, code_offset, intrinsic_ordinal>;

struct code_descriptor {
   digest_type code_hash;
   uint8_t vm_version;
   uint8_t codegen_version;
   size_t code_begin;
   mosvmoc_optional_offset_or_import_t start;
   unsigned apply_offset;
   int starting_memory_pages;
   size_t initdata_begin;
   unsigned initdata_size;
   unsigned initdata_prologue_size;
};

enum mosvmoc_exitcode : int {
   MOSVMOC_EXIT_CLEAN_EXIT = 1,
   MOSVMOC_EXIT_CHECKTIME_FAIL,
   MOSVMOC_EXIT_SEGV,
   MOSVMOC_EXIT_EXCEPTION
};

}}}

FC_REFLECT(mos::chain::mosvmoc::no_offset, );
FC_REFLECT(mos::chain::mosvmoc::code_offset, (offset));
FC_REFLECT(mos::chain::mosvmoc::intrinsic_ordinal, (ordinal));
FC_REFLECT(mos::chain::mosvmoc::code_descriptor, (code_hash)(vm_version)(codegen_version)(code_begin)(start)(apply_offset)(starting_memory_pages)(initdata_begin)(initdata_size)(initdata_prologue_size));

#define MOSVMOC_INTRINSIC_INIT_PRIORITY __attribute__((init_priority(198)))