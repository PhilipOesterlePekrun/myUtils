#pragma once

#include <mu_core_Strings.hpp>
  
// // DEBUG FUNCTIONALITY
namespace MyUtils::Db {

// debug print
inline void pr(const std::string& s = "", int level = 0) {
  #ifdef myUtils_DbPr_ON
  std::string sTot = "-- DEBUG PRINT --\n"+s+"\n";
  std::cout<<levelizeString(sTot, level);
  #endif
}

// Standard warning output
inline void warn(const std::string& s, int level = 0) {
  #ifdef myUtils_DbPr_ON
  std::string sTot = "-- WARNING --\n"+s+"\n";
  std::cout<<levelizeString(sTot, level);
  #endif
}

} // namespace MyUtils::Db
