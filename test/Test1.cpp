#include "Test1.hpp"

#include "mu.hpp"

using namespace std;
using namespace MyUtils;

int Test1(int argCount, char** args) {
  std::string str = "012345";
  std::vector v = MyUtils::Strings::checkForIn("1", str);
  
  std::cout<<"-Test 1.1:\n";
  std::cout<<"v.size()="<<v.size()<<"\n";
  if(v[0]==1) std::cout<<"-Passed"<<"\n"; 
  else std::cout<<"-Failed"<<"\n";
  
  std::cout<<"-Test 1.2:\n";
  if(MyUtils::Math::CommonFunctions::step(-1) == 0) std::cout<<"-Passed"<<"\n";
  else std::cout<<"-Failed"<<"\n";
  
  
  std::string testDelimiter = "----------------------------------------------------\n";
  
  std::cout<<"Start test main"<<"\n";
  
  {
    std::cout<<testDelimiter;
    std::cout<<"Print Matrix2d"<<"\n";
    auto m = LinAlg::Matrix2d(2, 3,
      {
        11, 12, 13,
        21, 22, 33
      }
    );
    m.print();
    std::cout<<"m.rowAt(1).print();\n";
    m.rowAt(1).print();
    std::cout<<"m.colAt(1).print();\n";
    m.colAt(1).print();
  }
  
  {
    std::cout<<testDelimiter;
    double ξ = 2.0;
    int א = 20;
    std::cout<<"Testing non-ASCII variable names:\n\tξ="<<ξ<<"\tא="<<א<<"\n";
  }
  
  /*{
    std::cout<<testDelimiter;
    std::cout<<"Testing LinAlg::Array\n";
    vector<int> arr{{0, 2, 4, 6, 8, 10, 12}};
    arr.print();
    arr.deleteIndices(Array<size_t>{{2, 0}});
    arr.print();
    std::cout<<arr.toString();
  }*/
  
  {
    using namespace Strings;
    
    std::cout<<testDelimiter;
    std::cout<<"Testing Global.hpp string utils\n";
    vector<std::string> strArr{{"0\n", "1"}};
    std::cout<<"strArrayToStr(strArr):\n"<<strArrayToStr(strArr);
    std::cout<<"strToStrArray";
    //std::cout<<strToStrArray(strArrayToStr(strArr)).toString();
    
    std::string testStr = "01234 |q|\n 56 | 78 | ww";
    std::cout<<alignStringAt(testStr, "|");
  }
  
  return 0;
}
