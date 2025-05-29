#include "HelloFunction.hpp"

/** Using Legacy Pass
#define DEBUG_TYPE "hello"

bool HelloFunction::runOnFunction(Function &F) {
    return false;
}

void HelloFunction::getAnalysisUsage(AnalysisUsage &AU) const {
    AU.setPreservesAll();
}

char HelloFunction::ID = 0;
static RegisterPass<HelloFunction> Y("HelloFunction", "Hello World! Pass");
*/

llvm::PreservedAnalyses HelloFunctionPass::run(const llvm::Function &F, llvm::FunctionAnalysisManager &FAM) {
    llvm::errs() << "Hello from Function: " << F.getName() << "\n";
    return llvm::PreservedAnalyses::all();
}