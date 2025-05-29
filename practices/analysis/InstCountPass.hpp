#ifndef INSTCOUNTPASS_HPP
#define INSTCOUNTPASS_HPP

#include "llvm/IR/Function.h"
#include "llvm/IR/PassManager.h"

struct InstCountPass : llvm::PassInfoMixin<InstCountPass> {
    static llvm::PreservedAnalyses run(llvm::Function &F, llvm::FunctionAnalysisManager &FAM);
};

#endif //INSTCOUNTPASS_HPP
