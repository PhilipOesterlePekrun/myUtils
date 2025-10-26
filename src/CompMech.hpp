#pragma once
#include "Core.hpp"

#include <iostream>
#include <string>
#include <math.h>
#include <limits>
#include <numbers>

namespace MyUtils::CompMech {

struct fieldExtrema {
  double max = std::numeric_limits<double>::min(); // default access modifier is public for structs btw

  int iMax = -1;
  int jMax = -1;
  int nMax = -1;
  double min = std::numeric_limits<double>::max();
  int iMin = -1;
  int jMin = -1;
  int nMin = -1;

  void print() {
    std::cout << "Field Extrema: max " << (*this).max << " @ " << (*this).iMax << ", " << (*this).jMax << ", " << (*this).nMax <<
    " | min " << (*this).min << " @ " << (*this).iMin << ", " << (*this).jMin << ", " << (*this).nMin << "\n";
  }
  void setExtrema(double fieldVal, int i, int j, int n) {
    if (fieldVal > this->max) {
      this->max = fieldVal;
      this->iMax = i;
      this->jMax = j;
      this->nMax = n;
    }
    if (fieldVal < this->min) {
      this->min = fieldVal;
      this->iMin = i;
      this->jMin = j;
      this->nMin = n;
    }
  }
};

}
