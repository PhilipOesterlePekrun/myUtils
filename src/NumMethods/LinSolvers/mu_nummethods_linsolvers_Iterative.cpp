#include "mu_nummethods_linsolvers_Iterative.hpp"

namespace MyUtils::NumMethods::LinSolvers {
using namespace LinAlg;

Vectord Jacobi(Matrix2d A, Vectord b, int maxiter, double maxRelResNorm, int printEvery) {
  MU_STATUS("Starting Jacobi solver...");
  
  const int n = A.nRows();
  auto L = A;
  auto U = A;
  auto D = A;
  for(int i=0; i<n; ++i)
    for(int j=0; j<n; ++j) {
      if(j>=i)
        L(i, j) = 0;
      if(i>=j)
        U(i, j) = 0;
      if(i!=j)
        D(i, j) = 0;
    }
    
  auto residual = [&](Vectord& x){return vectdPlusVectd(mat2dTimesVectd(A, x), scaleVectd(-1.0, b));};
  auto residualNorm = [&](Vectord& x){auto res = residual(x); return vectdDotVectd(res, res);};
  Vectord x_0(n); // Initial guess, zeros here
  auto relativeResidualNorm = [&](Vectord& x){return residualNorm(x)/residualNorm(x_0);};
  Vectord x_i = x_0;
  int iter = 0;
  
  /*MyUtils::Db::pr("K L U D");
  K.print();
  L.print();
  U.print();
  D.print();*/
  
  auto invD = D;
  for(int i=0; i<n; ++i)
    if(invD(i, i) != 0)
      invD(i, i) = 1.0/D(i, i);
  invD.print();

  while(iter < maxiter && [&](Vectord& x_iIn){if(maxRelResNorm==-1.0) return true; else return relativeResidualNorm(x_iIn) > maxRelResNorm;}(x_i)) {
    x_i = mat2dTimesVectd(invD,
      vectdPlusVectd(b,
        scaleVectd(-1.0,
          mat2dTimesVectd(mat2dPlusMat2d(L, U),
            x_i))));
            
    if(printEvery>0&&iter%printEvery==0) {
      constexpr int baseSpaceCount = 5;
      std::string msg = "Iter "+std::to_string(iter)+Strings::repeatStr(" ", 5+std::to_string(maxiter).length()-std::to_string(iter).length());
      msg+="relResNorm="+std::format("{:.10e}", relativeResidualNorm(x_i))+"\n";
      //std::cout<<"residual = ";
      //residual(x_i).print(8);
      //std::cout<<"x_i = ";
      //x_i.print(8);
      std::cout<<msg;
    }
    
    ++iter;
  }
  
  if(printEvery>0) std::cout<<"\n";
  
  return x_i;
}

// Set printEvery to -1 for no printing
Vectord GaussSeidel(Matrix2d A, Vectord b, int maxiter, double maxRelResNorm, int printEvery) {
  MU_STATUS("Starting Gauss-Seidel solver...");
  
  const int n = A.nRows();
  auto L = A;
  auto U = A;
  for(int i=0; i<n; ++i)
    for(int j=0; j<n; ++j) {
      if(j>i)
        L(i, j) = 0;
      else// if(i>=j)
        U(i, j) = 0;
    }
    
  auto residual = [&](Vectord& x){return vectdPlusVectd(mat2dTimesVectd(A, x), scaleVectd(-1.0, b));};
  auto residualNorm = [&](Vectord& x){auto res = residual(x); return vectdDotVectd(res, res);};
  Vectord x_0(n); // Initial guess, zeros here
  auto relativeResidualNorm = [&](Vectord& x){return residualNorm(x)/residualNorm(x_0);};
  Vectord x_i = x_0;
  int iter = 0;
  
  /*MyUtils::Db::pr("K L U");
  K.print();
  L.print();
  U.print();*/

  while(iter < maxiter && [&](Vectord& x_iIn){if(maxRelResNorm==-1.0) return true; else return relativeResidualNorm(x_iIn) > maxRelResNorm;}(x_i)) {
    x_i = LinAlg::solveLxb(L,
      vectdPlusVectd(b,
        scaleVectd(-1.0,
          mat2dTimesVectd(U, x_i))));
    
    if(printEvery>0&&iter%printEvery==0) {
      constexpr int baseSpaceCount = 5;
      std::string msg = "Iter "+std::to_string(iter)+Strings::repeatStr(" ", 5+std::to_string(maxiter).length()-std::to_string(iter).length());
      msg+="relResNorm="+std::format("{:.10e}", relativeResidualNorm(x_i))+"\n";
      //std::cout<<"residual = ";
      //residual(x_i).print(8);
      //std::cout<<"x_i = ";
      //x_i.print(8);
      std::cout<<msg;
    }
    
    ++iter;
  }
  
  if(printEvery>0) std::cout<<"\n";
  
  return x_i;
}

} // namespace MyUtils::NumMethods::LinSolvers
