#pragma once

#include <mu_core_Strings.hpp>
#include <iostream>
  
// // DEBUG FUNCTIONALITY
namespace MyUtils::Db {

// debug print
inline void pr(const std::string& s = "", int level = 0) {
  #ifdef myUtils_DbPr_ON
  //std::string sTot = "-- DEBUG PRINT --\n"+s+"\n";
  std::cout<<Strings::levelizeString(s, level);
  #endif
}

// Standard warning output
inline void warn(const std::string& s, int level = 0) {
  #ifdef myUtils_DbPr_ON
  std::string sTot = "-- WARNING --\n"+s+"\n";
  std::cout<<Strings::levelizeString(sTot, level);
  #endif
}

// TODO: maybe put this in a different file. It doesnt really fit Strings or IO, but maybe a status and cout specific file in Db. Or a printing specific file in core, where things like levelizestring can alos maybe go. like Strings_IO or Strings_Printing maybe idk
class LoadingBar {
  const int size_;
  const int centerLength_;
  const int initialIndent_;
  
  int i_ = 0;
  int progress_ = 0;
  
 public:
  LoadingBar(int size, int centerLength, int initialIndent = 0)
  : size_(size), centerLength_(centerLength), initialIndent_(initialIndent) {}
  
  void operator()() {
    if (size_ <= 0 || centerLength_ <= 0) return;

    if (i_ == 0) {
      std::cout << std::string(initialIndent_, ' ') << "[";
    }

    int targetProgress = ((i_ + 1) * centerLength_) / size_;

    while (progress_ < targetProgress) {
      if (centerLength_ >= 10 &&
          progress_ != 0 &&
          progress_ % (centerLength_ / 10) == 0) {
        std::cout << "|";
      } else {
        std::cout << "=";
      }
      ++progress_;
    }

    ++i_;

    if (i_ == size_) {
      std::cout << "]\n";
    }

    std::cout.flush();
  }
};

} // namespace MyUtils::Db
