#include <iostream>

extern "C" void traceMalloc (const void *addr, const size_t size) {
    std::cout << "[Memory Allocation] Addr: " << addr << " Size: " << size << std::endl;
}

extern "C" void traceLoad (const void *addr, const size_t size) {
    std::cout << "[Load] Addr: " << addr << " Size: " << size << std::endl;
}

extern "C" void traceStore (const void *addr, const size_t size) {
    std::cout << "[Store] Addr: " << addr << " Size: " << size << std::endl;
}