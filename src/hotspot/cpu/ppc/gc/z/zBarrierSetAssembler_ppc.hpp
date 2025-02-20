/*
 * Copyright (c) 2021, Oracle and/or its affiliates. All rights reserved.
 * Copyright (c) 2021 SAP SE. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 */

#ifndef CPU_PPC_GC_Z_ZBARRIERSETASSEMBLER_PPC_HPP
#define CPU_PPC_GC_Z_ZBARRIERSETASSEMBLER_PPC_HPP

#include "code/vmreg.hpp"
#include "oops/accessDecorators.hpp"
#ifdef COMPILER2
#include "opto/optoreg.hpp"
#endif // COMPILER2

#ifdef COMPILER1
class LIR_Assembler;
class LIR_OprDesc;
typedef LIR_OprDesc* LIR_Opr;
class StubAssembler;
class ZLoadBarrierStubC1;
#endif // COMPILER1

#ifdef COMPILER2
class Node;
class ZLoadBarrierStubC2;
#endif // COMPILER2

class ZBarrierSetAssembler : public ZBarrierSetAssemblerBase {
public:
  virtual void load_at(MacroAssembler* masm, DecoratorSet decorators, BasicType type,
                       Register base, RegisterOrConstant ind_or_offs, Register dst,
                       Register tmp1, Register tmp2,
                       MacroAssembler::PreservationLevel preservation_level, Label *L_handle_null = NULL);

#ifdef ASSERT
  virtual void store_at(MacroAssembler* masm, DecoratorSet decorators, BasicType type,
                        Register base, RegisterOrConstant ind_or_offs, Register val,
                        Register tmp1, Register tmp2, Register tmp3,
                        MacroAssembler::PreservationLevel preservation_level);
#endif // ASSERT

  virtual void arraycopy_prologue(MacroAssembler* masm, DecoratorSet decorators, BasicType type,
                                  Register src, Register dst, Register count,
                                  Register preserve1, Register preserve2);

  virtual void try_resolve_jobject_in_native(MacroAssembler* masm, Register dst, Register jni_env,
                                             Register obj, Register tmp, Label& slowpath);

#ifdef COMPILER1
  void generate_c1_load_barrier_test(LIR_Assembler* ce,
                                     LIR_Opr ref,
                                     LIR_Opr res) const;

  void generate_c1_load_barrier_stub(LIR_Assembler* ce,
                                     ZLoadBarrierStubC1* stub) const;

  void generate_c1_load_barrier_runtime_stub(StubAssembler* sasm,
                                             DecoratorSet decorators) const;
#endif // COMPILER1

#ifdef COMPILER2
  OptoReg::Name refine_register(const Node* node, OptoReg::Name opto_reg) const;

  void generate_c2_load_barrier_stub(MacroAssembler* masm, ZLoadBarrierStubC2* stub) const;
#endif // COMPILER2
};

#endif // CPU_AARCH64_GC_Z_ZBARRIERSETASSEMBLER_AARCH64_HPP
