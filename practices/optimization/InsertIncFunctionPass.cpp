#include "InsertIncFunctionPass.hpp"

#include <llvm/Passes/PassBuilder.h>
#include <llvm/Passes/PassPlugin.h>
#include <llvm/IR/IRBuilder.h>

llvm::PreservedAnalyses InsertIncFunctionPass::run(llvm::Module &M, llvm::ModuleAnalysisManager &MAM) {

    /** Create a function in Function Class */
    std::vector<llvm::Type *> formals(1);
    formals[0] = llvm::Type::getInt64Ty(M.getContext());
    llvm::FunctionType *incFunType = llvm::FunctionType::get(llvm::Type::getInt64Ty(M.getContext()), formals, false);
    llvm::Function *incFun = llvm::Function::Create(incFunType, llvm::GlobalValue::InternalLinkage, "inc", &M);

    /** Create a basic block for inc function */
    llvm::BasicBlock *incEntry = llvm::BasicBlock::Create(M.getContext(), "entry", incFun);

    /** Create IR Builder and Fill Basic Block with instructions */
    llvm::IRBuilder<> builder(incEntry);
    llvm::Value *res = builder.CreateAdd(incFun->arg_begin(), llvm::ConstantInt::get(llvm::Type::getInt64Ty(M.getContext()), 1));
    builder.CreateRet(res);

    return llvm::PreservedAnalyses::none(); // IR 수정 시에는 none으로 변경
}

extern "C" llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
    return {
        LLVM_PLUGIN_API_VERSION,
        "InsertIncFunctionPass",
        LLVM_VERSION_STRING,
        [](llvm::PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](const llvm::StringRef name, llvm::ModulePassManager &MPM,
                   llvm::ArrayRef<llvm::PassBuilder::PipelineElement>) -> bool {
                    if (name == "InsertIncFunctionPass") {
                        MPM.addPass(InsertIncFunctionPass());
                        return true;
                    }
                    return false;
                }
            );
        }
    };
}
