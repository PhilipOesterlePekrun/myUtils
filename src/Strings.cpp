#include "Strings.hpp"

#include <math.h>

#include "Arrays.hpp"

namespace Utils::Strings {

int* checkForIn(const std::string& checkFor, const std::string& checkIn, int returnArrayLength) {
  int* returnArray =(int*)malloc(returnArrayLength*sizeof(int));
  for (int i = 0; i <returnArrayLength; i++) {
    returnArray[i] = -1;
  }
  std::string checkInTemp = checkIn;
  int arrayPos = 0;
  if (checkFor.length()<= checkIn.length()) {
    for (int i = 0; i <= checkIn.length() - checkFor.length() && arrayPos < returnArrayLength; i++) {
      //checkInTemp = deleteInterval(checkInTemp, i, checkInTemp.Length);
      for (int j = 0; j < checkFor.length() && arrayPos < returnArrayLength; j++) {
        if (checkFor[j] != checkIn[i + j]) break;
        if (j == checkFor.length() - 1) {
          returnArray[arrayPos] = i;
          arrayPos++;
        }
      }
    }
  }
  return returnArray;
}

int* checkForIn_withDataLastEle(const std::string& checkFor, const std::string& checkIn, int returnCount) {
  int* returnArray =(int*)malloc((returnCount+1)*sizeof(int));
  for (int i = 0; i <returnCount; i++)
    returnArray[i] = -1;
  
  if (checkFor.length() >= checkIn.length())
    returnArray[returnCount - 1] = 0;
  else {
    std::string checkInTemp = checkIn;
    int arrayPos = 0;
    for (int i = 0; i <= checkIn.length() - checkFor.length() && arrayPos < returnCount+1; i++) {
      for (int j = 0; j < checkFor.length() && arrayPos < returnCount+1; j++) {
        if (checkFor[j] != checkIn[i + j]) break;
        if (j == checkFor.length() - 1) {
          if(arrayPos < returnCount)
            returnArray[arrayPos] = i;
          arrayPos++;
        }
      }
    }
    returnArray[returnCount] = arrayPos;
  }
  return returnArray;
}

int getEndOfWhitespace(const std::string& checkIn) {
  int i = 0;
  while(checkIn[i]==' ' || checkIn[i]=='\t')
    i++;
  return i;
}

//can be composed easily; from==0 --> char 0 deleted, to>=length --> last char deleted; from==to --> one char at that pos deleted
std::string deleteInterval(const std::string& text, int from, int to) {
  std::string temp = "";
  //int j = 0;
  for (int i = 0; i < text.length(); i++) {
    if (!(i >= from && i <= to)) {
      temp = temp + text[i];
      //temp[j] = text[i];
      //j++;
    }
  }
  return temp;
}

// fully inclusive [from,to]
std::string keepInterval(const std::string& text, int from, int to) {
  return deleteInterval(deleteInterval(text, 0, from - 1), to - from + 1, text.length()); // text.Length always greater so it is fine
}

// e.g. "-2.0952600000e-02" to -0.029526; expNotationToDouble("254.045e-01", 7, 2) correctly output 25.4045
double expNotationToDouble(const std::string& expText, int mantissaCharCount, int expCharCount) {
  short isNegative = 0;
  if (expText.at(0) == '-')
  {
    isNegative = 1;
  }
  std::string left = keepInterval(expText, 0, mantissaCharCount-1+isNegative);
  std::string expSignString = keepInterval(expText, mantissaCharCount+1+isNegative, mantissaCharCount+1+isNegative);
  std::string right = keepInterval(expText, mantissaCharCount+2+isNegative, mantissaCharCount+1+expCharCount+isNegative);

  int sign = 0;
  if (expSignString == "+") sign = 1;
  else if (expSignString == "-") sign = -1;
  
  return std::stod(left) * pow(10, sign * std::stoi(right));
}

std::string trimZerosAfterDecimalPoint(const std::string& str) {
  if(checkForIn(".", str, 1)[0]==-1) return str;

  int pos=str.length()-1;
  while(str[pos]=='0') {
    pos--;
  }
  if(str[pos]=='.') pos--;

  return deleteInterval(str, pos+1, str.length());
}

// cf. replaceKeywordsAndWriteFile
void replaceKeyword(std::vector<std::string>* stringArr, const std::string& kwText, const std::string& replace, int linesOut, int maxPerLine) {
  for(int i = 0; i<linesOut; i++) {
    int* checkForInArr;
    Arrays::allocate1DArray<int>(&checkForInArr, maxPerLine);
    
    int j=0;
    while(true) {
      checkForInArr = checkForIn(kwText, stringArr->at(i), maxPerLine);
      if(checkForInArr[0]==-1) break;

      std::string tmpLine = stringArr->at(i);
      stringArr->at(i) = deleteInterval(tmpLine, checkForInArr[0], tmpLine.length())+replace+deleteInterval(tmpLine, 0, checkForInArr[0]+kwText.length()-1);
      j++;
    }
    
    free(checkForInArr);
  }
}

}
