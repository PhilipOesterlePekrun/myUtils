#pragma once
#include "MyArray_decl.hpp"

#include <iostream>

namespace MyUtils::MyArray {

// TODO: Also this should be a better structure so it looks better
// deprecated; use toString()
template<typename T>
inline void Array<T>::print(int eleStrLen) const { //# we make inline for now
  std::cout<<"[";
  FOR(i, size_) {
    std::string tmpStr;
    if constexpr (std::is_same<T, std::string>::value)
      tmpStr = (*this)(i);
    else
      tmpStr = std::to_string((*this)(i));
    std::string tmpStr2;
    for(int s=0; s<eleStrLen; ++s) {
      if(s >= tmpStr.length())
        tmpStr2 += " ";
      else
        tmpStr2 +=tmpStr[s];
    }
    std::cout<<tmpStr2;
    if(i<size_-1)
      std::cout<<" ";
  }
  std::cout<<"]^T\n\n";
}
template<typename T>
inline std::string Array<T>::toString(int eleStrLen) const { //# we make inline for now
  std::string out = "[";
  FOR(i, size_) {
    std::string tmpStr;
    if constexpr (std::is_same<T, std::string>::value)
      tmpStr = (*this)(i);
    else
      tmpStr = std::to_string((*this)(i));
    std::string tmpStr2;
    for(int s=0; s<eleStrLen; ++s) {
      if(s >= tmpStr.length())
        tmpStr2 += " ";
      else
        tmpStr2 +=tmpStr[s];
    }
    out += tmpStr2;
    if(i<size_-1)
      out += " ";
  }
  out += "]^T\n\n";
  
  return out;
}

}
