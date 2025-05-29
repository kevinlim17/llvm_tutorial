#ifndef HELLOMODULE_HPP
#define HELLOMODULE_HPP

#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/IR/PassManager.h"

/** Using Legacy Pass
using namespace llvm;

struct HelloModule : llvm::ModulePass {
    static char ID;
    HelloModule() : ModulePass(ID) {}

    bool runOnModule(llvm::Module &M) override;

    void getAnalysisUsage(llvm::AnalysisUsage &AU) const override;
};
*/

struct HelloModulePass : llvm::PassInfoMixin<HelloModulePass> {
    static llvm::PreservedAnalyses run(const llvm::Module &M, llvm::ModuleAnalysisManager &MAM);
};


#endif //HELLOMODULE_HPP
