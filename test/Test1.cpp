#include "Test1.hpp"

#include "mu_core_Strings.hpp"
#include "mu_core_Math.hpp"

int Test1(int argCount, char** args) {
  std::string str = "012345";
  std::vector v = MyUtils::Strings::checkForIn("1", str);
  
  std::cout<<"Test 1.1: ";
  if(v[0]==1 && v[1]==-1) std::cout<<"Passed"<<"\n"; 
  else std::cout<<"Failed"<<"\n";
  
  std::cout<<"Test 1.2: ";
  if(MyUtils::Math::CommonFunctions::step(-1) == 0) std::cout<<"Passed"<<"\n";
  else std::cout<<"Failed"<<"\n";
  
  THROW("wwwww");
  
  return 0;
}
