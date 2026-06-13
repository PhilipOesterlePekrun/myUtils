#pragma once
#include "mu_core_GlobalCore.hpp"

#include <string>
#include <vector>

#include "mu_core_Strings.hpp"

namespace MyUtils::IO {
  
std::string findFileWithString(const std::string& dir, const std::string& substring);

int countFilesInFolder(const std::string& dirPath, const bool recursive);

[[deprecated("Use the more aptly named readFileToStr()")]]
std::string readFileFromStr(const std::string& filePath);

std::string readFileToStr(const std::string& filePath);
void writeFileFromStr(const std::string& filePath, const std::string& str, bool chmodX = false);
  
void readFileLines(const std::string& filePath, std::vector<std::string>& strVect);
std::vector<std::string> readFileLines(const std::string& filePath);

void writeFileLines(const std::string& filePath, std::string* lines, int lineCount);
void writeFileLines(const std::string& filePath, std::vector<std::string>* lines);
void writeFileLines(const std::string& filePath, const std::vector<std::string>& lines, bool chmodX = false);
void writeFileLinesBinary(const std::string& filePath, std::string* lines, int lineCount);
void writeFileLinesBinary(const std::string& filePath, std::vector<std::string>* lines);

std::string stringVect2DToCSV(std::vector<std::vector<std::string>> strVect, int xCount, int yCount);

void replaceKeywordsAndWriteFile(std::string& filePathInAbs, std::string& folderOutAbs, std::string& fileNameOut, std::string* keywords, std::string* replacements, int lengthKwArr, bool onlyCopy = false, int maxLines = strAndIO_maxLinesDefault);

}
