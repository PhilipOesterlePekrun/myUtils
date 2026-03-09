#pragma once
#include "mu_core_GlobalCore.hpp"

#include "mu_core_LinAlg.hpp"

// Basic numerical methods
namespace MyUtils::NumMethods {
using namespace LinAlg;

// returns [smallerX, largerX], real solution of ax^2 + bx + c = 0; throws error if any imaginary solution
inline Vectord solveScalarQuadraticEq(double a, double b, double c);

} // namespace MyUtils::NumMethods
