#pragma once

#include <stdexcept> // required for MU_THROW()

// // HELPER MACROS

#define FOR(i, ...) for (int i = 0; __VA_OPT__(i < (__VA_ARGS__)) ; ++i)
// Because the below doesn't work:
//#define FOR(i, n) for(int i = 0; i < (n); ++i)
//#define FOR(i) for(int i = 0;; ++i)

#define MU_STATUS(msg) std::cout<<"MU_STATUS: "<<msg<<"\n";
#define MU_THROW(msg) throw std::runtime_error(msg)
