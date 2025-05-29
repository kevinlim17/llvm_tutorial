#ifndef LOOPANALYSISPASS_HPP
#define LOOPANALYSISPASS_HPP

#include "llvm/IR/PassManager.h"
#include "llvm/Analysis/LoopInfo.h"

struct LoopAnalysisPass : llvm::PassInfoMixin<LoopAnalysisPass> {
    static llvm::PreservedAnalyses run(llvm::Function &F, llvm::FunctionAnalysisManager &FAM);
};


#endif
