#pragma once
#include "mu_core_GlobalCore.hpp"

#include <vector>

#include "mu_core_Math.hpp"

namespace MyUtils::NumIntegration {

/*
double integrateTrapz(double (*f)(double), double l, double r, double n) {
  double h = (r - l) / n;
  double result = 0;
  for(int i=0; i<n-1; ++i) {
    result += (f(i*h) + f((i+1)*h))/2.0 * h;
  }
  return result;
}
*/

template<typename Fct>
double trapezoidal(Fct f, double n, double l, double r) {
  double h = (r - l) / n;
  double result = 0;
  for(int i=0; i<n-1; ++i) {
    result += (f(i*h) + f((i+1)*h))/2.0 * h;
  }
  return result;
}
  
using std::vector;
const vector<vector<double>> gaussPoints = {
  {0},
  {-sqrt(1.0/3), sqrt(1.0/3)},
  {-sqrt(3.0/5), 0, sqrt(3.0/5)},
  {-sqrt(3.0/7+2.0/7*sqrt(6.0/5)), -sqrt(3.0/7-2.0/7*sqrt(6.0/5)), sqrt(3.0/7-2.0/7*sqrt(6.0/5)), sqrt(3.0/7+2.0/7*sqrt(6.0/5))},
  {-1.0/3*sqrt(5.0+2.0*sqrt(10.0/7)), -1.0/3*sqrt(5.0-2.0*sqrt(10.0/7)), 0, 1.0/3*sqrt(5.0-2.0*sqrt(10.0/7)), 1.0/3*sqrt(5.0+2.0*sqrt(10.0/7))}
};
const vector<vector<double>> gaussWeights = {
  {2},
  {1, 1},
  {5.0/9, 8.0/9, 5.0/9},
  {18.0-sqrt(30.0), 18.0+sqrt(30.0), 18.0+sqrt(30.0), 18.0-sqrt(30.0)},
  {(322.0-13.0*sqrt(70.0))/900, (322.0+13.0*sqrt(70.0))/900, 128.0/225, (322.0+13.0*sqrt(70.0))/900, (322.0-13.0*sqrt(70.0))/900}
};

template<typename Fct>
double gaussianQuadrature(Fct f, int m, bool mIsPolyOrder_else_numgp = true) {
  int numgp;
  if(!mIsPolyOrder_else_numgp)
    numgp = m;
  else
    // polyDegree < 2*numgp-1
    numgp = std::ceil((double)m/2)+1;
    
  if(numgp>gaussPoints.size())
    MU_THROW("gaussianQuadrature(): only up to numgp="+std::to_string(gaussPoints.size())+" gauss points supported currently");
  
  auto& points = gaussPoints[numgp-1];
  auto& weights = gaussWeights[numgp-1];
  double result = 0;
  FOR(i, numgp)
    result += f(points[i])*weights[i];
  return result;
}

template<typename Fct>
double gaussianQuadrature(Fct f, int m, double l, double r, bool mIsPolyOrder_else_numgp = true) {
  const double half = 0.5*(r - l);
  const double mid  = 0.5*(l + r);

  auto transformedFct = [&](double xi) {
    return f(mid + half*xi) * half;
  };

  return gaussianQuadrature(transformedFct, m, mIsPolyOrder_else_numgp);
}
  
} // namespace MyUtils::NumIntegration
