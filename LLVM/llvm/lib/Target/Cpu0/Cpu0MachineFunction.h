//===-- Cpu0MachineFunctionInfo.h - Private data used for Cpu0 ----*- C++ -*-=//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the Cpu0 specific subclass of MachineFunctionInfo.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_CPU0_CPU0MACHINEFUNCTION_H
#define LLVM_LIB_TARGET_CPU0_CPU0MACHINEFUNCTION_H



#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineMemOperand.h"
#include "llvm/CodeGen/PseudoSourceValue.h"
#include "llvm/Target/TargetMachine.h"
#include <map>

namespace llvm {

//@1 {
/// Cpu0FunctionInfo - This class is derived from MachineFunction private
/// Cpu0 target-specific information for each MachineFunction.
  class Cpu0FunctionInfo : public MachineFunctionInfo {
  public:
  //不符合接口规范
    // Cpu0FunctionInfo(MachineFunction& MF)
    //     : MF(MF),
    //       VarArgsFrameIndex(0),
    //       SRetReturnReg(0), CallsEhReturn(false), CallsEhDwarf(false),
    //       MaxCallFrameSize(0)
    //       , EmitNOAT(false)
    // {}
    Cpu0FunctionInfo(const Function &F, const TargetSubtargetInfo *STI) {}
    //还一个clone构造函数不知道干什么的
    ~Cpu0FunctionInfo();

    unsigned getSRetReturnReg() const { return SRetReturnReg; }
    void setSRetReturnReg(unsigned Reg) { SRetReturnReg = Reg; }

    int getVarArgsFrameIndex() const { return VarArgsFrameIndex; }
    void setVarArgsFrameIndex(int Index) { VarArgsFrameIndex = Index; }
    bool getEmitNOAT() const { return EmitNOAT; }
    void setEmitNOAT() { EmitNOAT = true; }

    bool hasByvalArg() const { return HasByvalArg; }
    void setFormalArgInfo(unsigned Size, bool HasByval) {
      IncomingArgSize = Size;
      HasByvalArg = HasByval;
    }

  private:
    virtual void anchor();

    //MachineFunction& MF;
    /// SRetReturnReg - Some subtargets require that sret lowering includes
    /// returning the value of the returned struct in a register. This field
    /// holds the virtual register into which the sret argument is passed.
    unsigned SRetReturnReg = 0;

    /// True if function has a byval argument.
    bool HasByvalArg  = false;

    /// Size of incoming argument area.
    unsigned IncomingArgSize = 0;

    /// CallsEhReturn - Whether the function calls llvm.eh.return.
    bool CallsEhReturn  = false;

    /// CallsEhDwarf - Whether the function calls llvm.eh.dwarf.
    bool CallsEhDwarf  = false;

    /// Frame objects for spilling eh data registers.
    int EhDataRegFI[2];

    /// VarArgsFrameIndex - FrameIndex for start of varargs area.
    int VarArgsFrameIndex = 0;

    unsigned MaxCallFrameSize = 0;

    bool EmitNOAT = false;
  };
//@1 }

} // end of namespace llvm

#endif // CPU0_MACHINE_FUNCTION_INFO_H

