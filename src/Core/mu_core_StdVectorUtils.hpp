#pragma once
#include "mu_core_GlobalCore.hpp"

#include <vector>
#include <iostream>

namespace MyUtils::StdVectorUtils {

using std::vector;

template<typename T>
inline std::string toString(const vector<T>& v, int eleStrLen = 5) { //# we make inline for now
  std::string out = "[";
    for(int i=0; i<v.size(); ++i) {
      std::string tmpStr;
      if constexpr (std::is_same<T, std::string>::value)
        tmpStr = v[i];
      else
        tmpStr = std::to_string(v[i]);
      std::string tmpStr2;
      for(int s=0; s<eleStrLen; ++s) {
        if(s >= tmpStr.length())
          tmpStr2 += " ";
        else
          tmpStr2 +=tmpStr[s];
      }
      out+=tmpStr2;
      if(i<v.size()-1)
        out+=" ";
    }
    out+="]^T\n";
    
    return out;
}

template<typename T>
inline void print(const vector<T>& v, int eleStrLen = 5) {
  std::cout<<toString(v, eleStrLen);
}

template<typename T>
vector<size_t> find(const vector<T>& v, T val) {
  vector<size_t> arr;
  FOR(i, v.size()) {
    if(v[i] == val)
      arr.push_back(i);
  }
  return arr;
}

// It is safe for [indicesToDelete] to have dupicates; they will be ignored
template<typename T>
void deleteIndices(vector<T>& v, const vector<size_t>& indicesToDelete) {
  vector<char> del(v.size(), false);
  for (size_t i : indicesToDelete) {
    if (i < del.size()) del[i] = true;  // ignore out-of-range
  }

  vector<T> out;
  out.reserve(v.size());
  for (size_t i = 0; i < v.size(); ++i) {
    if (!del[i]) out.push_back(std::move(v[i]));
  }
  v = std::move(out);
}
  
  /*
  template<typename T>
  void deleteIndices(vector<T>& v, const Array<int>& indicesToDelete) { // TODO: think about which we want. size_t or int or both possibly but also maybe not very good to have both
    Array<size_t> keepIndices;
    for (size_t i = 0; i < size_; ++i) {
      if(indicesToDelete.find((size_t)i).size()==0)
        keepIndices.push_back(i);
    }

    std::vector<T> newData(keepIndices.size());
    for (size_t iNew = 0; iNew < keepIndices.size(); ++iNew) {
      size_t iOld = keepIndices(iNew);
      newData[iNew] = (*this)(iOld);
    }

    size_ = keepIndices.size();
    data_ = std::move(newData);
  }
*/


} // namespace MyUtils::StdVectorUtils
