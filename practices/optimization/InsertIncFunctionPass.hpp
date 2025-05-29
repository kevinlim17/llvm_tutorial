#ifndef INSERTINCFUNCTIONPASS_HPP
#define INSERTINCFUNCTIONPASS_HPP

#include "llvm/IR/Module.h"
#include "llvm/IR/PassManager.h"

struct InsertIncFunctionPass : llvm::PassInfoMixin<InsertIncFunctionPass> {
   llvm::PreservedAnalyses run(llvm::Module &M, llvm::ModuleAnalysisManager &MAM);
};

#endif
