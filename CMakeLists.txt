cmake_minimum_required(VERSION 3.20) # 3.20 이상 권장
project(llvm_tutorial)

# C++20 Standard 설정
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# LLVM Package 찾기
find_package(LLVM REQUIRED CONFIG)

# LLVM 정보 출력
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# LLVM 관련 Directory 추가
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# 메인 실행 파일 추가
add_executable(llvm_tutorial
        practices/analysis/HelloModule.hpp
        practices/analysis/HelloModule.cpp
        practices/analysis/HelloFunction.hpp
        practices/analysis/HelloFunction.cpp
        practices/analysis/LoopAnalysisPass.hpp
        practices/analysis/LoopAnalysisPass.cpp
        practices/analysis/InstCountPass.hpp
        practices/analysis/InstCountPass.cpp
        practices/analysis/CallInstCountPass.hpp
        practices/analysis/CallInstCountPass.cpp
        practices/optimization/InsertIncFunctionPass.hpp
        practices/optimization/InsertIncFunctionPass.cpp
        practices/optimization/LoadTracerPass.hpp
        practices/optimization/LoadTracerPass.cpp
        practices/optimization/LoadTracerRuntime.cpp
        practices/optimization/DynamicCallCountPass.hpp
        practices/optimization/DynamicCallCountPass.cpp
        practices/memory_profiler/MemoryProfilerPass.hpp
        practices/memory_profiler/MemoryProfilerPass.cpp
        practices/memory_profiler/MemoryProfilerRuntime.cpp
        practices/optimization/CallCount.cpp
)

# LLVM Component 정의
llvm_map_components_to_libnames(llvm_libs
        support
        core
        irreader
        passes
        transformutils
        practices
        ipo
        scalaropts
        instcombine
        profiledata
        target
)

# 타겟 링크 설정
target_link_libraries(llvm_tutorial PRIVATE ${llvm_libs})