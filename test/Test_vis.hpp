#pragma once
#include "mu_core_GlobalCore.hpp"

#include "mu_vis.hpp"
#include "mu_core_Math.hpp"

using namespace MyUtils;

#include <map>
std::vector<std::vector<double>> getAsArr(std::map<int, double> map, bool inTermsOfN = false) {
  auto arr = std::vector<std::vector<double>>();
  for (const auto& [key, value] : map) {
    if(inTermsOfN) {
      int N = (1 << static_cast<int>(key)) + 1;
      arr.push_back(std::vector<double>{{(double)N, value}});
    }
    else
      arr.push_back(std::vector<double>{{static_cast<double>(key), value}});
  }
  return arr;
}
double InterpolatedShapeFactor(const std::map<int, double>& shapeFactors, int N)
    {
      double resolution = log2(N - 1);
      int resfloor = (int)std::floor(resolution);
      double sf_floor = shapeFactors.at(resfloor);
      if (((N - 1) & (N - 2)) == 0) return sf_floor;
      return sf_floor + (resolution - resfloor) * (shapeFactors.at(resfloor + 1) - sf_floor);
    }
int Test_vis(int argCount, char** args) {
  MU_STATUS("Test_vis START\n")
  
  sf::Font* timesNewRoman = new sf::Font("/home/oesterle/misc/myBasicFemSolver_Base/myBasicFemSolver/data//fonts/times.ttf");
  
  const std::map<int, double> shape_factors_force{{1, 0.778958541513360}, {2, 0.805513388666376},
    {3, 0.826126871395416}, {4, 0.841369158110513}, {5, 0.851733020725652}, {6, 0.858342234203154},
    {7, 0.862368243479785}, {8, 0.864741597831785}};
  const std::map<int, double> shape_factors_pressure{{1, 0.961389237917602}, {2, 0.924715342432435},
    {3, 0.899837531880697}, {4, 0.884976751041942}, {5, 0.876753783192863}, {6, 0.872397956576882},
    {7, 0.8701463093314326}, {8, 0.8689982669426167}};
  
    Vis::VisualizationBase visf, visfn, visp, vispn;
  {
    const std::map<int, double>& fp = shape_factors_force;
    
    auto shape_factors_force_XY = getAsArr(fp);
    auto shape_factors_force_XY_N = getAsArr(fp, true);
    
    visf = Vis::VisualizationBase("FORCE not N", 1200, 1400, 20, sf::Color(255, 255, 255), sf::Color(5, 5, 5), sf::Color(0, 0, 0), timesNewRoman, 12);
    Vis::Graph* g = new Vis::Graph(100, 100, 1000, 800, shape_factors_force_XY);
    visf.attachObjects(std::vector<Vis::Object*>{{g}});
    visf.activate();
    
    visfn = Vis::VisualizationBase("FORCE N", 1200, 1400, 20, sf::Color(255, 255, 255), sf::Color(5, 5, 5), sf::Color(0, 0, 0), timesNewRoman, 12);
    Vis::Graph* g2 = new Vis::Graph(100, 100, 1000, 800, shape_factors_force_XY_N);
    visfn.attachObjects(std::vector<Vis::Object*>{{g2}});
    visfn.activate();
    
    //while(visf.active_){visf.drawFrame();visfn.drawFrame();}
  }
  
  {
    const std::map<int, double>& fp = shape_factors_pressure;
    
    auto shape_factors_force_XY = getAsArr(fp);
    auto shape_factors_force_XY_N = getAsArr(fp, true);
    
    
    
    visp = Vis::VisualizationBase("PRESSURE not N", 1200, 1400, 20, sf::Color(255, 255, 255), sf::Color(5, 5, 5), sf::Color(0, 0, 0), timesNewRoman, 12);
    Vis::Graph* g = new Vis::Graph(100, 100, 1000, 800, shape_factors_force_XY);
    visp.attachObjects(std::vector<Vis::Object*>{{g}});
    visp.activate();
    
    vispn = Vis::VisualizationBase("PRESSURE N", 1200, 1400, 20, sf::Color(255, 255, 255), sf::Color(5, 5, 5), sf::Color(0, 0, 0), timesNewRoman, 12);
    Vis::Graph* g2 = new Vis::Graph(100, 100, 1000, 800, shape_factors_force_XY_N);
    vispn.attachObjects(std::vector<Vis::Object*>{{g2}});
    vispn.activate();
    
    
  }
  
  while(visf.isActive()) {
    visf.drawFrame();visfn.drawFrame();
    
    visp.drawFrame();vispn.drawFrame();
    
    visf.play();
    if(visf.currentTime().asSeconds()>5) visf.deactivate()&&visfn.deactivate()&&visp.deactivate();
  }
  
  MU_STATUS("Test_vis END\n")
  return 0;
}
