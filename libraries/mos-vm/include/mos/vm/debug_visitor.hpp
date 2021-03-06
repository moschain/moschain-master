#pragma once

#include <mos/vm/interpret_visitor.hpp>
#include <mos/vm/opcodes.hpp>

#include <iostream>

#define DBG_VISIT(name, code)                                                                                          \
   void operator()(MOS_VM_OPCODE_T(name)& op) {                                                                        \
      std::cout << "Found " << #name << " at " << get_context().get_pc() << "\n";                                      \
      interpret_visitor<ExecutionCTX>::operator()(op);                                                                 \
      get_context().print_stack();                                                                                     \
   }

#define DBG2_VISIT(name, code)                                                                                         \
   void operator()(MOS_VM_OPCODE_T(name)& op) { std::cout << "Found " << #name << "\n"; }

namespace mos { namespace vm {

template <typename ExecutionCTX>
struct debug_visitor : public interpret_visitor<ExecutionCTX> {
   using interpret_visitor<ExecutionCTX>::operator();
   debug_visitor(ExecutionCTX& ctx) : interpret_visitor<ExecutionCTX>(ctx) {}
   ExecutionCTX& get_context() { return interpret_visitor<ExecutionCTX>::get_context(); }
   MOS_VM_CONTROL_FLOW_OPS(DBG_VISIT)
   MOS_VM_BR_TABLE_OP(DBG_VISIT)
   MOS_VM_RETURN_OP(DBG_VISIT)
   MOS_VM_CALL_OPS(DBG_VISIT)
   MOS_VM_CALL_IMM_OPS(DBG_VISIT)
   MOS_VM_PARAMETRIC_OPS(DBG_VISIT)
   MOS_VM_VARIABLE_ACCESS_OPS(DBG_VISIT)
   MOS_VM_MEMORY_OPS(DBG_VISIT)
   MOS_VM_I32_CONSTANT_OPS(DBG_VISIT)
   MOS_VM_I64_CONSTANT_OPS(DBG_VISIT)
   MOS_VM_F32_CONSTANT_OPS(DBG_VISIT)
   MOS_VM_F64_CONSTANT_OPS(DBG_VISIT)
   MOS_VM_COMPARISON_OPS(DBG_VISIT)
   MOS_VM_NUMERIC_OPS(DBG_VISIT)
   MOS_VM_CONVERSION_OPS(DBG_VISIT)
   MOS_VM_EXIT_OP(DBG_VISIT)
   MOS_VM_ERROR_OPS(DBG_VISIT)
};

struct debug_visitor2 {
   MOS_VM_CONTROL_FLOW_OPS(DBG2_VISIT)
   MOS_VM_BR_TABLE_OP(DBG2_VISIT)
   MOS_VM_RETURN_OP(DBG2_VISIT)
   MOS_VM_CALL_OPS(DBG2_VISIT)
   MOS_VM_CALL_IMM_OPS(DBG2_VISIT)
   MOS_VM_PARAMETRIC_OPS(DBG2_VISIT)
   MOS_VM_VARIABLE_ACCESS_OPS(DBG2_VISIT)
   MOS_VM_MEMORY_OPS(DBG2_VISIT)
   MOS_VM_I32_CONSTANT_OPS(DBG2_VISIT)
   MOS_VM_I64_CONSTANT_OPS(DBG2_VISIT)
   MOS_VM_F32_CONSTANT_OPS(DBG2_VISIT)
   MOS_VM_F64_CONSTANT_OPS(DBG2_VISIT)
   MOS_VM_COMPARISON_OPS(DBG2_VISIT)
   MOS_VM_NUMERIC_OPS(DBG2_VISIT)
   MOS_VM_CONVERSION_OPS(DBG2_VISIT)
   MOS_VM_EXIT_OP(DBG2_VISIT)
   MOS_VM_ERROR_OPS(DBG2_VISIT)
};
#undef DBG_VISIT
#undef DBG2_VISIT

#undef DBG_VISIT
#undef DBG2_VISIT

}} // ns mos::wasm_backend
