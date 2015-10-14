#include "components/visionComponent.h"


VisionComponent::VisionComponent(sf::Vector2f location, float l, float dir, float a)
:xy(location), length(l), direction(dir), coneAngle(a)
{
  this->setType(VISION);
  alert = false;
  visionResolution = 5;

  triFan = new sf::VertexArray(sf::TrianglesFan, 1 + coneAngle/this->getVisionResolution());
}
