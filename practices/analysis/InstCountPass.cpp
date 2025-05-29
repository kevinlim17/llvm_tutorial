#include "InstCountPass.hpp"

#include <llvm/Passes/PassBuilder.h>
#include <llvm/Passes/PassPlugin.h>

llvm::PreservedAnalyses InstCountPass::run(llvm::Function &F, llvm::FunctionAnalysisManager &FAM) {
    int count = 0;
    for (llvm::BasicBlock &BB: F) {
        for (llvm::Instruction &I: BB) {
            count += 1;
        }
    }
    llvm::errs() << "Function: " << F.getName() << " has " << count << " instructions\n";
    return llvm::PreservedAnalyses::all();
}

extern "C" llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
    return {
        LLVM_PLUGIN_API_VERSION,
        "InstCountPass",
        LLVM_VERSION_STRING,
        [](llvm::PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](const llvm::StringRef name, llvm::FunctionPassManager &FPM,
                   llvm::ArrayRef<llvm::PassBuilder::PipelineElement>) -> bool {
                    if (name == "InstCountPass") {
                        FPM.addPass(InstCountPass());
                        return true;
                    }
                    return false;
                }
            );
        }
    };
}
