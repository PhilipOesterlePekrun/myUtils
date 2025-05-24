#pragma once

#include <string>
#include <vector>

namespace Utils {
  
constexpr int strAndIO_maxLinesDefault = 50000;

}

namespace Utils::Strings {

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

}
