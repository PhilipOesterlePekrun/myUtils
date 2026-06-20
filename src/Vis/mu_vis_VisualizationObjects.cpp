#include "mu_vis_VisualizationObjects.hpp"

#include "mu_vis_VisualizationBase.hpp"

#include <SFML/Graphics.hpp>

#include <algorithm>
#include <cmath>

namespace MyUtils::Vis {
  
void Object::attach(VisualizationBase* vis) {
  vis_ = vis;
  visWindow_ = &vis->renderWindow_;
  attached_ = true;
}
void Object::detach() {
  // I don't think it actually matters if the members continue to have dangling pointers
  attached_ = false;
}
  
void Graph::draw() const {
  const float posX = static_cast<float>(posX_);
  const float posY = static_cast<float>(posY_);
  const float width = static_cast<float>(width_);
  const float height = static_cast<float>(height_);
  constexpr float axisThickness = 5.0f;
  constexpr float plotInset = 2.0f;

  visWindow_->draw(vis_->textConstructorXY("X-axis", posX + width / 2.0f, posY - 10.0f));
  sf::RectangleShape xAxis(sf::Vector2f(width, axisThickness));
  xAxis.setPosition(vis_->Vector2fInXY(posX, posY));
  xAxis.setFillColor(sf::Color(0, 0, 0));
  visWindow_->draw(xAxis);
  
  visWindow_->draw(vis_->textConstructorXY("Y-axis", posX - 50.0f, posY + height / 2.0f));
  sf::RectangleShape yAxis(sf::Vector2f(axisThickness, height));
  yAxis.setPosition(vis_->Vector2fInXY(posX, posY + height));
  yAxis.setFillColor(sf::Color(0, 0, 0));
  visWindow_->draw(yAxis);

  bool hasValidPoint = false;
  std::size_t validPointCount = 0;
  double minX = 0.0;
  double maxX = 0.0;
  double minY = 0.0;
  double maxY = 0.0;

  for (const auto& point : graphDataXY_) {
    if (point.size() < 2 || !std::isfinite(point[0]) || !std::isfinite(point[1])) {
      continue;
    }

    const double x = point[0];
    const double y = point[1];
    if (!hasValidPoint) {
      minX = maxX = x;
      minY = maxY = y;
      hasValidPoint = true;
    } else {
      minX = std::min(minX, x);
      maxX = std::max(maxX, x);
      minY = std::min(minY, y);
      maxY = std::max(maxY, y);
    }
    ++validPointCount;
  }

  if (!hasValidPoint) {
    return;
  }

  auto expandDegenerateRange = [](double& minValue, double& maxValue) {
    if (minValue == maxValue) {
      const double padding = std::max(std::abs(minValue) * 0.05, 1.0);
      minValue -= padding;
      maxValue += padding;
    }
  };

  expandDegenerateRange(minX, maxX);
  expandDegenerateRange(minY, maxY);

  visWindow_->draw(vis_->textConstructorXY(std::to_string(minX), posX, posY - 10.0f));
  visWindow_->draw(vis_->textConstructorXY(std::to_string(maxX), posX + width, posY - 10.0f));
  visWindow_->draw(vis_->textConstructorXY(std::to_string(minY), posX - 50.0f, posY));
  visWindow_->draw(vis_->textConstructorXY(std::to_string(maxY), posX - 50.0f, posY + height));

  const float plotWidth = std::max(width - 2.0f * plotInset, 0.0f);
  const float plotHeight = std::max(height - 2.0f * plotInset, 0.0f);

  auto graphPointToWindowPoint = [&](double x, double y) {
    const double xRatio = (x - minX) / (maxX - minX);
    const double yRatio = (y - minY) / (maxY - minY);
    return vis_->Vector2fInXY(
      posX + plotInset + plotWidth * static_cast<float>(xRatio),
      posY + plotInset + plotHeight * static_cast<float>(yRatio)
    );
  };

  if (validPointCount == 1) {
    for (const auto& point : graphDataXY_) {
      if (point.size() < 2 || !std::isfinite(point[0]) || !std::isfinite(point[1])) {
        continue;
      }

      sf::CircleShape pointShape(3.0f);
      pointShape.setOrigin(sf::Vector2f(3.0f, 3.0f));
      pointShape.setPosition(graphPointToWindowPoint(point[0], point[1]));
      pointShape.setFillColor(vis_->secondaryColor_);
      visWindow_->draw(pointShape);
      return;
    }
  }

  sf::VertexArray lines(sf::PrimitiveType::LineStrip, validPointCount);
  std::size_t lineIndex = 0;
  for (const auto& point : graphDataXY_) {
    if (point.size() < 2 || !std::isfinite(point[0]) || !std::isfinite(point[1])) {
      continue;
    }

    lines[lineIndex].position = graphPointToWindowPoint(point[0], point[1]);
    lines[lineIndex].color = vis_->secondaryColor_;
    ++lineIndex;
  }
  visWindow_->draw(lines);
}

} // namespace MyUtils::Vis
