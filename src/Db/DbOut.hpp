#pragma once

#include <Strings.hpp>
  
// // DEBUG FUNCTIONALITY
namespace MyUtils::Db {

// debug print
inline void pr(const std::string& s = "", int level = 0) { // TODO: make this shorter by using levelizeString()
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

// Throw an error
inline void throwAndExit(const std::string& msg = "") {
  std::cout<<"\n"<<msg<<"\n";
  std::exit(1);
}

} // namespace MyUtils::Db
