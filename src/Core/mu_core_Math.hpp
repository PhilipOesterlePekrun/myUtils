#pragma once
#include "mu_core_GlobalCore.hpp"

#include <iostream>
#include <math.h>
#include <numbers>

namespace MyUtils::Math {
  
inline constexpr double pi = (double)3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822317253594081284811174502841027019385211055596446229489549303819644288109756659334461284756482337867831652712019;

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

inline double inv(double d) {
  if(d==0.0)
    return 0.0;
  return 1.0/d;
}

}

}
