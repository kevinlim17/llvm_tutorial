#include "DynamicCallCountPass.hpp"

#include <llvm/Passes/PassBuilder.h>
#include <llvm/Passes/PassPlugin.h>

llvm::PreservedAnalyses DynamicCallCountPass::run(llvm::Module &M, llvm::ModuleAnalysisManager &) {
    /** Define the function type */
    llvm::Type *voidType = llvm::Type::getVoidTy(M.getContext());
    llvm::FunctionType *funcType = llvm::FunctionType::get(voidType, false);

    /** GetOrInsert Functions */
    auto countCallCallee = M.getOrInsertFunction("countCall", funcType);
    auto *countCall = llvm::dyn_cast<llvm::Function>(countCallCallee.getCallee());

    auto printResultCallee = M.getOrInsertFunction("printResult", funcType);
    auto *printResult = llvm::dyn_cast<llvm::Function>(printResultCallee.getCallee());

    for (llvm::Function &F: M) {
        for (llvm::BasicBlock &BB: F) {
            for (llvm::Instruction &I: BB) {
                if (auto *CountCall = llvm::dyn_cast<llvm::CallInst>(&I); CountCall != nullptr) {
                    llvm::IRBuilder<> builder(CountCall);
                    builder.CreateCall(countCall);
                }
                else if (auto *Ret = llvm::dyn_cast<llvm::ReturnInst>(&I); Ret != nullptr) {
                    llvm::IRBuilder<> builder(Ret);
                    builder.CreateCall(printResult);
                }
            }
        }
    }

    return llvm::PreservedAnalyses::none();
}


extern "C" llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
    return {
        LLVM_PLUGIN_API_VERSION,
        "DynamicCallCountPass",
        LLVM_VERSION_STRING,
        [](llvm::PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](const llvm::StringRef name, llvm::ModulePassManager &MPM,
                   llvm::ArrayRef<llvm::PassBuilder::PipelineElement>) -> bool {
                    if (name == "DynamicCallCountPass") {
                        MPM.addPass(DynamicCallCountPass());
                        return true;
                    }
                    return false;
                }
            );
        }
    };
}
