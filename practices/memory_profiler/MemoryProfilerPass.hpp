#ifndef MEMORYPROFILERPASS_HPP
#define MEMORYPROFILERPASS_HPP

#include <llvm/IR/Module.h>
#include <llvm/IR/PassManager.h>

struct MemoryProfilerPass : llvm::PassInfoMixin<MemoryProfilerPass> {
    static llvm::PreservedAnalyses run(llvm::Module &M, llvm::ModuleAnalysisManager &MAM);
};

#endif //MEMORYPROFILERPASS_HPP
