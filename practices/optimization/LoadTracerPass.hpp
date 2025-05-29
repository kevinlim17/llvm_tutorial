#ifndef LOADTRACERPASS_HPP
#define LOADTRACERPASS_HPP

#include <llvm/IR/Module.h>
#include <llvm/IR/PassManager.h>

struct LoadTracerPass : llvm::PassInfoMixin<LoadTracerPass> {
    static llvm::PreservedAnalyses run(llvm::Module &M, llvm::ModuleAnalysisManager &MAM);
};

#endif //LOADTRACERPASS_HPP
