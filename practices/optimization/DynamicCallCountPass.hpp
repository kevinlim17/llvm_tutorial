#ifndef DYNAMICCALLCOUNTPASS_HPP
#define DYNAMICCALLCOUNTPASS_HPP

#include <llvm/IR/Module.h>
#include <llvm/IR/PassManager.h>

struct DynamicCallCountPass : llvm::PassInfoMixin<DynamicCallCountPass> {
    static llvm::PreservedAnalyses run(llvm::Module &M, llvm::ModuleAnalysisManager &MAM);
};

#endif //DYNAMICCALLCOUNTPASS_HPP
