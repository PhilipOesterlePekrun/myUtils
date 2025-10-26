#include "IO.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <math.h>
#include <limits>
#include <numbers>

namespace MyUtils::IO {

namespace fs = std::filesystem;

// TODO: add recursive option
std::string findFileWithString(const std::string& dir, const std::string& substring) {
  fs::path match;
  bool found = false;
  fs::path directory(dir);

  for (const auto& entry : fs::directory_iterator(directory)) {
    if (!entry.is_regular_file()) continue;

    std::string filename = entry.path().filename().string();
    if (filename.find(substring) != std::string::npos) {
      if (found) {
        std::cerr<<"Multiple files contain the target substring in the filename; return \"-2\""<<"\n";
      }
      match = entry.path();
      found = true;
    }
  }

  if (!found) {
    std::cerr<<"No file contains the target substring in the filename; return \"-1\""<<"\n";
  }

  return match.string();
}

int countFilesInFolder(const std::string& dirPath, const bool recursive) {
  int fileCount = 0;
  fs::path path(dirPath);

  if (!fs::exists(path) || !fs::is_directory(path)) {
    return -1; // or throw an error if invalid path
  }

  if (recursive) {
    for (const auto& entry : fs::recursive_directory_iterator(path)) {
      if (entry.is_regular_file()) {
        fileCount++;
      }
    }
  }
  else {
    for (const auto& entry : fs::directory_iterator(path)) {
      if (entry.is_regular_file()) {
        fileCount++;
      }
    }
  }

  return fileCount;
}

int readFileLines(const std::string& filePath, std::vector<std::string>* strVect, int maxLines) {
  std::ifstream inFile(filePath);
  int lineCount = 0;

  if (!inFile) {
    throw std::ios_base::failure("Error opening file: " + filePath);
  }
  
  if(strVect->size() == maxLines)
    while (lineCount < maxLines && std::getline(inFile, strVect->at(lineCount)))
      lineCount++;
  else {
    std::string lineTmp;
    while (lineCount < maxLines && std::getline(inFile, lineTmp)) {
      strVect->push_back(lineTmp);
      lineCount++;
    }
  }
    

  return lineCount;
}

void writeFileLines(const std::string& filePath, std::string* lines, int lineCount) {
  std::ofstream outFile(filePath);

  if (!outFile)
    throw std::ios_base::failure("Error writing to file: " + filePath);

  for (int i = 0; i < lineCount; i++) {
    outFile << lines[i];
    if(i < lineCount - 1)
      outFile << '\n';
  }
}
void writeFileLines(const std::string& filePath, std::vector<std::string>* lines) {
  std::ofstream outFile(filePath);

  if (!outFile)
    throw std::ios_base::failure("Error writing to file: " + filePath);

  for (int i = 0; i < lines->size(); i++) {
    outFile << lines->at(i);
    if(i < lines->size() - 1)
      outFile << '\n';
  }
}

void writeFileLinesBinary(const std::string& filePath, std::string* lines, int lineCount) {
  std::ofstream outFile(filePath, std::ios::binary); // Open in binary mode

  if (!outFile)
    throw std::ios_base::failure("Error writing to file: " + filePath);

  for (int i = 0; i < lineCount; i++) {
    outFile << lines[i];
    if(i < lineCount - 1)
      outFile << '\n';
  }
}
void writeFileLinesBinary(const std::string& filePath, std::vector<std::string>* lines) {
  std::ofstream outFile(filePath, std::ios::binary); // Open in binary mode

  if (!outFile)
    throw std::ios_base::failure("Error writing to file: " + filePath);

  for (int i = 0; i < lines->size(); i++) {
    outFile << lines->at(i);
    if(i < lines->size() - 1)
      outFile << '\n';
  }
}

// Kind of forced to use vect here? //#
std::string stringVect2DToCSV(std::vector<std::vector<std::string>> strVect, int xCount, int yCount) {
  std::string outString;
  for(int i=0; i<xCount; i++){
    for(int j=0; j<yCount-1; j++) {
      outString+=strVect[i][j]+",";
    }
    outString+=strVect[i][yCount-1];
    if(i!=xCount-1) outString+="\n";
  }
  return outString;
}

// cf. replaceKeyword
void replaceKeywordsAndWriteFile(std::string& filePathInAbs, std::string& folderOutAbs, std::string& fileNameOut, std::string* keywords, std::string* replacements, int lengthKwArr, bool onlyCopy, int maxLines) {
  std::string filePathOutFull = folderOutAbs+fileNameOut;

  std::vector<std::string> stringArr(maxLines);
  int linesOut=MyUtils::IO::readFileLines(filePathInAbs, &stringArr, maxLines);
  if(!onlyCopy) for(int i = 0; i < lengthKwArr; i++) {
    if(replacements[i]=="-") std::cerr<<"replacements["<<i<<"]==\"-\"\n";
    MyUtils::Strings::replaceKeyword(&stringArr, "-=-["+keywords[i]+"]-=-", replacements[i], linesOut);
  }

  std::filesystem::path filePathOutPath(filePathOutFull);
  std::filesystem::create_directory(filePathOutPath.parent_path());
  MyUtils::IO::writeFileLinesBinary(filePathOutFull, &stringArr);
}
  
}