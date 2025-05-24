#pragma once

#include <iostream>
#include <math.h>
#include <numbers>

#include "Constants.hpp"

namespace Utils::Math {

namespace CommonFunctions {

inline static double sigmoid(double x) {
  return 1 / (1 + exp(-x));
}

inline double step(double x) {
  if (x < 0) return 0;
  else return 1;
}

// returns angle in degrees, >= 0 and < 360
double atan2(double y, double x);

}

}
