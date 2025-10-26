#include "Test1.hpp"

#include "../src/Strings.hpp"
#include "../src/Math.hpp"

int Test1(int argCount, char** args) {
  std::string str = "012345";
  int* arr = MyUtils::Strings::checkForIn("1", str, 5);
  
  std::cout<<"Test 1.1: ";
  if(arr[0]==1 && arr[1]==-1) std::cout<<"Passed"<<"\n"; 
  else std::cout<<"Failed"<<"\n";
  
  free(arr);
  
  std::cout<<"Test 1.2: ";
  if(MyUtils::Math::CommonFunctions::step(-1) == 0) std::cout<<"Passed"<<"\n";
  else std::cout<<"Failed"<<"\n";
  
  return 0;
}
