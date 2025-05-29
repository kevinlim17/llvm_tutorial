#ifndef HELLOFUNCTION_HPP
#define HELLOFUNCTION_HPP

#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/IR/PassManager.h"

/** Using Legacy Pass
using namespace llvm;

struct HelloFunction : public FunctionPass {
    static char ID;
    HelloFunction() : FunctionPass(ID) {}

    bool runOnFunction(Function &F) override;

    void getAnalysisUsage(AnalysisUsage &AU) const override;
};
*/

struct HelloFunctionPass : llvm::PassInfoMixin<HelloFunctionPass> {
    static llvm::PreservedAnalyses run(const llvm::Function &F, llvm::FunctionAnalysisManager &FAM);
};

#endif //HELLOFUNCTION_HPP
