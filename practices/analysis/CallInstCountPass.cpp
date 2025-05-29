#include "CallInstCountPass.hpp"

#include <llvm/Passes/PassBuilder.h>
#include <llvm/Passes/PassPlugin.h>
#include <llvm/Passes/PassPlugin.h>

llvm::PreservedAnalyses CallInstCountPass::run(llvm::Function &F, llvm::FunctionAnalysisManager &FAM) {
    int callInstCount = 0;
    for (llvm::BasicBlock &BB: F) {
        for (llvm::Instruction &I: BB) {
            if (llvm::dyn_cast<llvm::CallInst>(&I) != nullptr) {
                callInstCount++;
            }
        }
    }
    llvm::errs() << "Function: " << F.getName() << " has " << callInstCount << " call instructions\n";
    return llvm::PreservedAnalyses::all();
}

extern "C" llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
    return {
        LLVM_PLUGIN_API_VERSION,
        "CallInstCountPass",
        LLVM_VERSION_STRING,
        [](llvm::PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](const llvm::StringRef name, llvm::FunctionPassManager &FPM,
                   llvm::ArrayRef<llvm::PassBuilder::PipelineElement>) -> bool {
                    if (name == "CallInstCountPass") {
                        FPM.addPass(CallInstCountPass());
                        return true;
                    }
                    return false;
                }
            );
        }
    };
}
