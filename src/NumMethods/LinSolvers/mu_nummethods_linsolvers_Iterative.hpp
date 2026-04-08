#pragma once
#include "mu_core_GlobalCore.hpp"

#include "mu_core_LinAlg.hpp"

// Iterative linear solvers for the system Ax=b
namespace MyUtils::NumMethods::LinSolvers {
using namespace LinAlg;

// Always define maxiter, but don't necessarily need maxRelResNorm (then set to -1.0)
// Set printEvery to -1 (default) for no printing, only the status message
Vectord Jacobi(Matrix2d A, Vectord b, int maxiter, double maxRelResNorm = -1.0, int printEvery = -1);

// Always define maxiter, but don't necessarily need maxRelResNorm (then set to -1.0)
// Set printEvery to -1 (default) for no printing, only the status message
Vectord GaussSeidel(Matrix2d A, Vectord b, int maxiter, double maxRelResNorm = -1.0, int printEvery = -1);

} // namespace MyUtils::NumMethods::LinSolvers
