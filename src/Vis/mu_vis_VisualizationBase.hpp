#pragma once
#include "mu_core_GlobalCore.hpp"

#include <SFML/Graphics.hpp>

#include "mu_vis_VisualizationObjects.hpp"
#include "mu_db.hpp"

namespace MyUtils::Vis {
  
using std::vector;
  
///class Object; // forward decl
  
class VisualizationBase {
  // UTILITIES (public because can also be used by visuaalization objects and such)
 public:
	sf::Vector2f Vector2fInXY(float posX, float posY){
		return sf::Vector2f(posX,windowHeight_-posY);
	}
  
	sf::Text textConstructorXY(const std::string& textString, float posX, float posY, int fontSize, sf::Color fillColor, sf::Font* font);
  // Overloads
  sf::Text textConstructorXY(const std::string& textString, float posX, float posY, int fontSize, sf::Color fillColor) {
    return textConstructorXY(textString, posX, posY, fontSize, fillColor, defaultFont_);
  };
  sf::Text textConstructorXY(const std::string& textString, float posX, float posY, int fontSize) {
    return textConstructorXY(textString, posX, posY, fontSize, defaultTextColor_, defaultFont_);
  };
  sf::Text textConstructorXY(const std::string& textString, float posX, float posY) {
    return textConstructorXY(textString, posX, posY, defaultFontSize_, defaultTextColor_, defaultFont_);
  };
  
  // CONSTRUCTORS
 public:
	VisualizationBase() {} // default constructor
	VisualizationBase(std::string title, int windowWidth, int windowHeight, int framerate, sf::Color baseColor, sf::Color secondaryColor, sf::Color defaultTextColor, sf::Font* defaultFont, int defaultFontSize);
	VisualizationBase(std::string title, int windowWidth, int windowHeight, int framerate, sf::Color baseColor, sf::Color secondaryColor, sf::Color defaultTextColor, sf::Font* defaultFont, int defaultFontSize, int antiAliasingLevel); // (antiAliasingLevel = 0) == off
  
  // LOGICAL FUNCTIONS
	bool activate();
	bool deactivate();
  bool isActive() const {return active_;}
	bool play();
	bool pause();
  bool goToFrame(int toFrame);
	bool goToTime(double toTime); // go to nearest time

  // DRAWING
 protected:
	void drawBaseUI(); //# should this be virtual or not idk?
 protected:
	virtual void drawFrameImplementation() {} // this has the logic to draw the frame, with the functions inserted into it
 private:
	bool pDown=false;
 public:
	void drawFrame(); // this just has all of the functions sequentially for drawing frame
  
  // VISUALIZATION OBJECTS
 private: // public because zero reason to be private or protected. just edit it directly, no issue.
  vector<Object*> objects_;
 public:
  // attaches additional objects, in addition to the ones already attached
  void attachObjects(const vector<Object*>& objects) { // TODO: these functions could be better named
    FOR(i, objects.size()) {
      if(objects[i]->isAttached())
        Db::warn("Some objects were already attached/activated and have not been attached as desired");
      else {
        objects_.push_back(objects[i]);
        objects[i]->attach(this); // yeah its the param but the element is a pointer, so this works
      }
    }
  }
  void clearObjects() {
    // TODO: this functions should empty objects_ and also deattach all of those elements
  }

  // GETTERS
  sf::Time currentTime() const {
    return sf::Time(sf::seconds((float)currentFrame_/framerate_));
  }
  uint currentFrame() const {
    return currentFrame_;
  }
  double getMaxTime() const {
    return (double)maxFrame_/framerate_;
  }
  uint getMaxFrame() const {
    return maxFrame_;
  }
  
/*static void loadFont(sf::Font *fontObj, std::string filePath) {
	if(!fontObj->loadFromFile(filePath)){
		std::cout<<"ERROR: Cannot load font"<<"\n";
	}
}*/
  
// MAIN MEMBER VARIABLES
 public:
  sf::RenderWindow renderWindow_;
	sf::Vector2i renderWindowPos_=sf::Vector2i(50, 50); // default, but you can change it from externally so you can open multiple simulation windows perfectly next to eachother
	std::string windowName_;
	uint windowWidth_;
	uint windowHeight_;
	uint framerate_;
	uint antiAliasingLevel_ = 0;
	sf::Color baseColor_; // == background color
	sf::Color secondaryColor_;
	sf::Color defaultTextColor_;
	sf::Font* defaultFont_;
	int defaultFontSize_ = 12; // might delete if it does not make sense

	uint currentFrame_=0; // or use time, idk
	bool active_=false; // active = window open
	bool paused_=true;
	bool playOnLoop_=true;
 protected:
	uint maxFrame_; // or maxFrame idk; in any case, it is taken from simulation in the constructor for everything except the Visualization base class
};

} // namespace MyUtils::Vis
