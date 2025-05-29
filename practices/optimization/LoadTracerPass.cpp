#include "LoadTracerPass.hpp"

#include <llvm/IR/Constants.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Passes/PassPlugin.h>

llvm::PreservedAnalyses LoadTracerPass::run(llvm::Module &M, llvm::ModuleAnalysisManager &MAM) {
    /** Define the Function Type */
    llvm::Type *voidType = llvm::Type::getVoidTy(M.getContext());
    llvm::PointerType *addrType = llvm::PointerType::getUnqual(M.getContext());
    llvm::Type *int64Type = llvm::Type::getInt64Ty(M.getContext());
    llvm::FunctionType *funcType = llvm::FunctionType::get(voidType, {addrType, int64Type}, false);

    // GetOrInsert Function
    auto callee = M.getOrInsertFunction("traceLoadInstr", funcType);
    auto *traceLoadInstr = llvm::dyn_cast<llvm::Function>(callee.getCallee());

    for (llvm::Function &F: M) {
        for (llvm::BasicBlock &BB: F) {
            for (llvm::Instruction &I: BB) {
                if (auto *Load = llvm::dyn_cast<llvm::LoadInst>(&I); Load != nullptr) {
                    llvm::Value* address = Load->getPointerOperand();
                    llvm::Value* opCode = llvm::ConstantInt::get(int64Type, I.getOpcode());

                    llvm::IRBuilder<> builder(Load->getNextNode());
                    builder.CreateCall(traceLoadInstr, {address, opCode});
                }
            }
        }
    }
    return llvm::PreservedAnalyses::none();
}


extern "C" llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
    return {
        LLVM_PLUGIN_API_VERSION,
        "LoadTracerPass",
        LLVM_VERSION_STRING,
        [](llvm::PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](const llvm::StringRef name, llvm::ModulePassManager &MPM,
                   llvm::ArrayRef<llvm::PassBuilder::PipelineElement>) -> bool {
                    if (name == "LoadTracerPass") {
                        MPM.addPass(LoadTracerPass());
                        return true;
                    }
                    return false;
                }
            );
        }
    };
}
