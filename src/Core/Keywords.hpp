#include "GlobalCore.hpp"

#include "MyArray.hpp"
#include "Strings.hpp"

namespace MyUtils::Keywords {
  
template<typename T>
using MyArray::Array<T>;
  
//# TODO, not working rn; also, make one for Array<std::string>, which just uses this or maybe more efficient to do it with another loop idk
std::string replaceKeywords(const std::string& inStr, Array<std::string> kws, Array<std::string> vals) {
  std::string res = inStr;
  
  FOR(i, kws.size()) {
    string kwFull = "__["+kws(i)+"]__";
    Array<int> cFI = MyUtils::Strings::checkForIn(kwFull, res);
    
    if(cFI.size()==0) continue;
    // else
    auto res2tmp = res;
    res = MyUtils::Strings::keepInterval(res2tmp, 0, cFI(0)-1) + vals(i);
    FOR(k, cFI.size()-1) {
      res += MyUtils::Strings::keepInterval(res2tmp, cFI(k)+kwFull.length(), cFI(k+1)) + vals(i);
    }
    res += MyUtils::Strings::keepInterval(res2tmp, cFI(cFI.size()-1)+kwFull.length(), res2tmp.length());
  }
}

} // namespace MyUtils::Keywords
