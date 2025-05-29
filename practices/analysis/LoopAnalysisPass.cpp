#include "LoopAnalysisPass.hpp"

#include <llvm/Passes/PassBuilder.h>
#include <llvm/Passes/PassPlugin.h>

llvm::PreservedAnalyses LoopAnalysisPass::run(llvm::Function &F, llvm::FunctionAnalysisManager &FAM) {
    int loopCount = 0;
    llvm::LoopInfo &LI = FAM.getResult<llvm::LoopAnalysis>(F);
    for (auto &L: LI) {
        llvm::errs() << "The depth of " << L->getName() << " Loop : " << L->getLoopDepth() << "\n";
        loopCount++;
    }
    llvm::errs() << "Function: " << F.getName() << " has " << loopCount << " loops\n";
    return llvm::PreservedAnalyses::all();
}



extern "C" llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
    return {
        LLVM_PLUGIN_API_VERSION,
        "LoopAnalysisPass",
        LLVM_VERSION_STRING,
        [](llvm::PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](const llvm::StringRef name, llvm::FunctionPassManager &FPM,
                   llvm::ArrayRef<llvm::PassBuilder::PipelineElement>) -> bool {
                    if (name == "LoopAnalysisPass") {
                        FPM.addPass(LoopAnalysisPass());
                        return true;
                    }
                    return false;
                }
            );
        }
    };
}