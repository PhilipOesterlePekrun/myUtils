#pragma once

#include <stdexcept>

// // HELPER MACROS

#define FOR(i, ...) for (int i = 0; __VA_OPT__(i < (__VA_ARGS__)) ; ++i)
// Because the below doesn't work:
//#define FOR(i, n) for(int i = 0; i < (n); ++i)
//#define FOR(i) for(int i = 0;; ++i)

#define MU_THROW(msg) throw std::runtime_error(msg)
