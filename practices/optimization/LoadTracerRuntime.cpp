#include <iostream>

extern "C" void traceLoadInstr(const void* addr, const u_int64_t instID) {
     std::cout << "Load Instruction: " << instID << " at " << addr << std::endl;
}