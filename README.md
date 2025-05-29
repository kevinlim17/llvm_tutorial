# How to Implement & Run LLVM Passes

---
Based on [LLVM 20.1.4](https://github.com/llvm/llvm-project/releases/tag/llvmorg-20.1.4)
---

## Abstract
- **Legacy Version of Pass**
    - C++ class that inherits the `Pass` class in LLVM
        - Implement functionality by overriding virtual methods
        - e.g., `runOnModule` or `runOnFunction`
- **New Version of Pass**
    - C++ class that inherits the `PassInfoMixIn` struct in `llvm/IR/PassManager.h`
    - Implement `PreservedAnalyses run (Module &M, ModuleAnalysisManager &AM);`

## Skeleton Code

1. Define the Module Pass in a Header File
```c++ title='HelloModule.hpp'
#include "llvm/IR/Module.h"  
#include "llvm/IR/PassManager.h"  

struct HelloModulePass : llvm::PassInfoMixin<HelloModulePass> {  
    static llvm::PreservedAnalyses run(
	    const llvm::Module &M, 
	    llvm::ModuleAnalysisManager &MAM);  
};  
```

2. Write the source for the module pass
```c++
llvm::PreservedAnalyses HelloModulePass::run(const llvm::Module &M, llvm::ModuleAnalysisManager &MAM) {  
    /** Some Code */
    return llvm::PreservedAnalyses::all();  /**If Editing IR, return PreservedAnalyses::None() */
}  
```

3. Register Pass
```c++
extern "C" llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {  
    return {  
        LLVM_PLUGIN_API_VERSION,  
        "HelloPass",  
        LLVM_VERSION_STRING,  
        [](llvm::PassBuilder &PB) {  
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
        }  
    };  
}
```

## Compile and Run Pass
1. Compile a pass and make it a shared-library
```shell
clang++ -fPIC -fno-rtti -shared \                                   
  HelloModule.cpp \
  `llvm-config --cxxflags --ldflags --libs core support passes` \
  -o [OUTPUT.so]
```

2. Run the LLVM pass using opt
```shell
opt -load-pass-plugin [OUTPUT.so] -passes=HelloModulePass [GENERATED_BITCODE] -o [OUTPUT]
```

## References
- [Writing An LLVM New PM Pass: LLVM.org](https://llvm.org/docs/WritingAnLLVMNewPMPass.html)


