#include "MemoryProfilerPass.hpp"

#include <llvm/IR/Instructions.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Passes/PassPlugin.h>

llvm::PreservedAnalyses MemoryProfilerPass::run(llvm::Module &M, llvm::ModuleAnalysisManager &MAM) {

    /** Define the function type */
    llvm::Type *voidType = llvm::Type::getVoidTy(M.getContext());
    llvm::PointerType *addrType = llvm::PointerType::getUnqual(M.getContext());
    llvm::Type *sizeType = llvm::Type::getIntNTy(M.getContext(), 64);
    llvm::Type *int8Type = llvm::Type::getInt8Ty(M.getContext());
    llvm::FunctionType *funcType = llvm::FunctionType::get(voidType, {addrType, sizeType}, false);

    /** GetOrInsert Function */
    auto traceMallocCallee = M.getOrInsertFunction("traceMalloc", funcType);
    auto *traceMalloc = llvm::dyn_cast<llvm::Function>(traceMallocCallee.getCallee());

    auto traceLoadCallee = M.getOrInsertFunction("traceLoad", funcType);
    auto *traceLoad = llvm::dyn_cast<llvm::Function>(traceLoadCallee.getCallee());

    auto traceStoreCallee = M.getOrInsertFunction("traceStore", funcType);
    auto *traceStore = llvm::dyn_cast<llvm::Function>(traceStoreCallee.getCallee());

   /** Data Layout */
    const llvm::DataLayout &Layout = M.getDataLayout();

    for (llvm::Function &F: M) {
        for (llvm::BasicBlock &BB: F) {
            for (llvm::Instruction &I: BB) {
                if (auto *Malloc = llvm::dyn_cast<llvm::CallInst>(&I); Malloc != nullptr) {
                    if (Malloc->getCalledFunction()->getName() == "malloc") {
                        llvm::IRBuilder<> builder(Malloc->getNextNode());

                        llvm::Value* address = Malloc;
                        llvm::Value* size = Malloc->getArgOperand(0);

                        builder.CreateCall(traceMalloc, {address, size});
                    }
                }
                else if (auto *Load = llvm::dyn_cast<llvm::LoadInst>(&I); Load != nullptr) {
                    llvm::IRBuilder<> builder(Load->getNextNode());

                    llvm::Value* address = Load->getPointerOperand();
                    llvm::TypeSize sizeInBit = Layout.getTypeSizeInBits(Load->getType());
                    llvm::Value* size = llvm::ConstantInt::get(sizeType, sizeInBit.getFixedValue());

                    builder.CreateCall(traceLoad, {address, size});
                }
                else if (auto *Store = llvm::dyn_cast<llvm::StoreInst>(&I); Store != nullptr) {
                    llvm::IRBuilder<> builder(Store);
                    llvm::Value* address = Store->getPointerOperand();

                    // builder.CreatePointerCast(Store->getValueOperand(), int8Type);
                    llvm::TypeSize sizeInBit = Layout.getTypeSizeInBits(Store->getValueOperand()->getType());
                    llvm::Value* size = llvm::ConstantInt::get(sizeType, sizeInBit.getFixedValue());

                    builder.CreateCall(traceStore, {address, size});
                }
            }
        }
    }

    return llvm::PreservedAnalyses::none();
}

extern "C" llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
    return {
        LLVM_PLUGIN_API_VERSION,
        "MemoryProfilerPass",
        LLVM_VERSION_STRING,
        [](llvm::PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](const llvm::StringRef name, llvm::ModulePassManager &MPM,
                   llvm::ArrayRef<llvm::PassBuilder::PipelineElement>) -> bool {
                    if (name == "MemoryProfilerPass") {
                        MPM.addPass(MemoryProfilerPass());
                        return true;
                    }
                    return false;
                }
            );
        }
    };
}
