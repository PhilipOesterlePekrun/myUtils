#pragma once
#include "Core.hpp"

#include <string>
#include <vector>

#include "MyArray.hpp"

namespace MyUtils {
  
constexpr int strAndIO_maxLinesDefault = 50000;

}

namespace MyUtils::Strings {

int* checkForIn(const std::string& checkFor, const std::string& checkIn, int returnArrayLength);

// variant where the last element (at returnCount) is not a position of something, but the length of the actual valid things. Thus, the size of the returned array is actually returnCount+1. If there were more instances of checkFor than there is space in the array, so more than returnCount, then the last element will be returnCount+1, so greater than the returnCount that is possible
int* checkForIn_withDataLastEle(const std::string& checkFor, const std::string& checkIn, int returnCount);

// This function basically sees any "\t" or " " characters at the beginning of the string and returns the position where these end and actual other characters begin (position of first non whitespace character is returned). Logically, it returns 0 if there is no starting whitespace and returns the full length if there is only whitespace
int getEndOfWhitespace(const std::string& checkIn);

//can be composed easily; from==0 --> char 0 deleted, to>=length --> last char deleted; from==to --> one char at that pos deleted
std::string deleteInterval(const std::string& text, int from, int to);

// fully inclusive [from,to]
std::string keepInterval(const std::string& text, int from, int to);

// e.g. "-2.0952600000e-02" to -0.029526; expNotationToDouble("254.045e-01", 7, 2) correctly output 25.4045
double expNotationToDouble(const std::string& expText, int mantissaCharCount, int expCharCount);

std::string trimZerosAfterDecimalPoint(std::string& str);

// cf. replaceKeywordsAndWriteFile
void replaceKeyword(std::vector<std::string>* stringArr, const std::string& kwText, const std::string& replace, int linesOut = strAndIO_maxLinesDefault, int maxPerLine = 20);



// // STRING UTILITIES INTENDED FOR EVENTUAL OUTPUT (TODOi: put these in myUtils eventually, but probably need to put Array and such in myUtils as well, which I should do anyways)
inline std::string repeatStr(const std::string& s, int count) {
  if(count <= 0)
    return "";
  std::string out = s;
  FOR(i, count-1)
    out += s;
  return out;
}

inline std::string levelizeString(const std::string& s, int level) {
  if(level == 0)
    return s;
  // else
  std::string lvlStr = repeatStr("\t", level);
  
  std::string tmpS = lvlStr;
  FOR(i, s.length()) {
    tmpS += s[i];
    if(s[i] == '\n' && i!=s.length()-1)// -1 because we don't want to turn the last "\n" into "\n\t", or else the next thing is affected
      tmpS += lvlStr;
  }
  return tmpS;
}

inline Array<std::string> strToStrArray(const std::string& s) {
  auto out = Array<std::string>();
  if(s == "") return out;
  out.push_back("");
  size_t sLength = s.length();
  FOR(i, sLength) {
    if(i!=sLength-1 && s[i]=='\n')
      out.push_back("");
    else if(s[i]!='\n')
      out(out.size()-1) += s[i];
  }
  return out;
}
inline std::string strArrayToStr(const Array<std::string>& a) {
  std::string out = "";
  FOR(i, a.size())
    out += a(i) + "\n";
  return out;
}

inline Array<int> checkForIn(const std::string& checkFor, const std::string& checkIn) { // TODOi: you have to move Array into myUtils so that you can also move this back into myUtils
  auto out = Array<int>();
  std::string checkInTemp = checkIn;
  if (checkFor.length() <= checkIn.length()) {
    for (int i = 0; i <= checkIn.length()-checkFor.length(); ++i) {
      //checkInTemp = deleteInterval(checkInTemp, i, checkInTemp.Length);
      FOR(j, checkFor.length()) {
        if (checkFor[j] != checkIn[i+j]) break;
        if (j == checkFor.length()-1) {
          out.push_back(i);
        }
      }
    }
  }
  return out;
}

// aligns the string rows at certain keys, like e.g. "|"" will be vertically aligned according to count (TODOm: make an overload for Array<std::string> where each ele is a row)
inline std::string alignStringAt(const std::string& s, const std::string& alignerKey) {
  auto a = strToStrArray(s);
  const int aSize = a.size();
  auto maxSpacing = Array<int>();
  Array<Array<int>> CFIs(aSize); // store for efficiency
  FOR(i, aSize) {
    auto cfi = checkForIn(alignerKey, a(i));
    CFIs(i) = cfi;
    if(cfi.size()==0)
      continue;
    maxSpacing.extend(cfi.size() - maxSpacing.size());
    if(cfi(0) > maxSpacing(0))
      maxSpacing(0) = cfi(0);
    FOR(j, cfi.size()-1)
      if(cfi(j+1)-cfi(j) > maxSpacing(j+1))
        maxSpacing(j+1) = cfi(j+1)-cfi(j);
  }
  auto aOut = Array<std::string>(aSize);
  FOR(i, aSize) {
    auto& cfi = CFIs(i);
    int dist = 0;
    int k = 0;
    FOR(j, a(i).length()) {
      if(k<cfi.size()) if(j == cfi(k)) {
        int diff = maxSpacing(k)-(cfi(k)-dist);
        aOut(i) += repeatStr(" ", diff);
        dist = cfi(k);
        ++k;
      }
      aOut(i) += a(i)[j];
    }
  }
  return strArrayToStr(aOut);
}

}
