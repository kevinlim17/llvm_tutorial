#ifndef CALLINSTCOUNTPASS_HPP
#define CALLINSTCOUNTPASS_HPP

#include "llvm/IR/Function.h"
#include "llvm/IR/PassManager.h"

struct CallInstCountPass : llvm::PassInfoMixin<CallInstCountPass> {
    static llvm::PreservedAnalyses run(llvm::Function &F, llvm::FunctionAnalysisManager &FAM);
};

#endif //CALLINSTCOUNTPASS_HPP

