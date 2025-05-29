#include "HelloModule.hpp"
#include "HelloFunction.hpp"
#include "LoopAnalysisPass.hpp"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Support/raw_ostream.h"

/** Using Legacy Pass
#define DEBUG_TYPE "hello"

bool HelloModule::runOnModule(Module &M) {
    return false;
}

void HelloModule::getAnalysisUsage(AnalysisUsage &AU) const {
    AU.setPreservesAll();
}

char HelloModule::ID = 0;
static RegisterPass<HelloModule> X("HelloModule", "Hello World! Pass");
*/

llvm::PreservedAnalyses HelloModulePass::run(const llvm::Module &M, llvm::ModuleAnalysisManager &MAM) {
    llvm::errs() << "Hello from Module: " << M.getName() << "\n";
    return llvm::PreservedAnalyses::all();
}

// opt가 Plugin을 인식하기 위해 필요한 함수
extern "C" llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
    return {
        LLVM_PLUGIN_API_VERSION,
        "HelloPass",
        LLVM_VERSION_STRING,
        [](llvm::PassBuilder &PB) {
            // Register Module Pass
            PB.registerPipelineParsingCallback(
                [](const llvm::StringRef name, llvm::ModulePassManager &MPM,
                   llvm::ArrayRef<llvm::PassBuilder::PipelineElement>) {
                    if (name == "HelloModulePass") {
                        MPM.addPass(HelloModulePass());
                        return true;
                    }
                    return false;
                }
            );
            PB.registerPipelineParsingCallback(
                // Register Function Pass
                [](const llvm::StringRef name, llvm::FunctionPassManager &FPM,
                   llvm::ArrayRef<llvm::PassBuilder::PipelineElement>) {
                    if (name == "HelloFunctionPass") {
                        FPM.addPass(HelloFunctionPass());
                        return true;
                    }
                    return false;
                }
            );
            /**
            PB.registerPipelineParsingCallback(
                // Register Loop Pass
                [](const llvm::StringRef name, llvm::FunctionPassManager &FPM,
                    llvm::ArrayRef<llvm::PassBuilder::PipelineElement>) {
                    if (name == "LoopInfoPass") {
                        llvm::LoopPassManager LPMdc;
                        LPM.addPass(LoopInfoPass());
                        // FPM.addPass((std::move(LPM)));
                        return true;
                    }
                    return false;
                }
            );
            */
        }
    };
}
