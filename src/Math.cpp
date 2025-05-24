#include "Math.hpp"

namespace Utils::Math {

namespace CommonFunctions {

double atan2(double y, double x) {
  if (x == 0) {
    if (y > 0) return 90;
    else if (y < 0) return 270;
    else return 0;
  }
  if (x > 0) {
    if(y>0) return 180 / Utils::Constants::pi * atan(y / x);
    else if (y < 0) return 270-180 / Utils::Constants::pi * atan(y / x);
    else return 0;
  }
  else {
    if (y == 0) return 180;
    else return 180 + 180 / Utils::Constants::pi * atan(y / x);
  }
}

}

}
