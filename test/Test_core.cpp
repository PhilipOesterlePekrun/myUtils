#include "Test_core.hpp"

#include "mu_core.hpp"

namespace {
  using namespace std;
  using namespace MyUtils;
}

int Test_core(int argCount, char** args) {
  MU_STATUS("Test_core START\n")
  
  string str = "012345";
  vector v = MyUtils::Strings::checkForIn("1", str);
  
  cout<<"-Test 1.1:\n";
  cout<<"v.size()="<<v.size()<<"\n";
  if(v[0]==1) cout<<"-Passed"<<"\n"; 
  else cout<<"-Failed"<<"\n";
  
  cout<<"-Test 1.2:\n";
  if(MyUtils::Math::CommonFunctions::step(-1) == 0) cout<<"-Passed"<<"\n";
  else cout<<"-Failed"<<"\n";
  
  
  string testDelimiter = "----------------------------------------------------\n";
  
  cout<<"Start test main"<<"\n";
  
  {
    cout<<testDelimiter;
    cout<<"Print Matrix2d"<<"\n";
    auto m = LinAlg::Matrix2d(2, 3,
      {
        11, 12, 13,
        21, 22, 33
      }
    );
    m.print();
    cout<<"m.rowAt(1).print();\n";
    m.rowAt(1).print();
    cout<<"m.colAt(1).print();\n";
    m.colAt(1).print();
  }
  
  {
    cout<<testDelimiter;
    double ξ = 2.0;
    int א = 20;
    cout<<"Testing non-ASCII variable names:\n\tξ="<<ξ<<"\tא="<<א<<"\n";
  }
  
  /*{
    cout<<testDelimiter;
    cout<<"Testing LinAlg::Array\n";
    vector<int> arr{{0, 2, 4, 6, 8, 10, 12}};
    arr.print();
    arr.deleteIndices(Array<size_t>{{2, 0}});
    arr.print();
    cout<<arr.toString();
  }*/
  
  {
    using namespace Strings;
    
    cout<<testDelimiter;
    cout<<"Testing Global.hpp string utils\n";
    vector<string> strArr ={"0\n", "1"};
    cout<<"strArrayToStr(strArr):\n"<<strArrayToStr(strArr);
    cout<<"strToStrArray";
    //cout<<strToStrArray(strArrayToStr(strArr)).toString();
    
    string testStr = "01234 |q|\n 56 | 78 | ww";
    cout<<alignStringAt(testStr, "|");
  }
  
  MU_STATUS("Test_core END\n")
  return 0;
}
