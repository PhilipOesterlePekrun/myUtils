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
  
  int i = 0;
  int progress = 0;
  
 public:
  LoadingBar(int size, int centerLength, int initialIndent = 0)
  : size_(size), centerLength_(centerLength), initialIndent_(initialIndent) {}
  
  void operator()() {
    if(i==0) std::cout<<Strings::repeatStr(" ", initialIndent_)<<"[";
    if(i==size_-1) std::cout<<"]\n";
    else
      if((double)i/size_>(double)progress/centerLength_) {
        if(progress!=0 && progress%(centerLength_/10)==0) std::cout<<"|"<<std::flush;
        else std::cout<<"="<<std::flush;
        ++progress;
      }
      
    ++i;
  }
};

} // namespace MyUtils::Db
