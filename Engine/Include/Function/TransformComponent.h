//
// Created by Echo on 2023/10/5.
//

#ifndef COSMOS_TRANSFORMCOMPONENT_H
#define COSMOS_TRANSFORMCOMPONENT_H
#include "Component.h"
#include "Core/Base/MathTypes.h"
#include "glm/detail/type_vec1.hpp"
#include "glm/vec3.hpp"

class TransformComponent : public Component {
  friend class GameObject;

private:
  explicit TransformComponent(GameObject *owner) : Component(owner) {}

public:
  glm::vec3 Position = Constant::Vec3::Zero;
  glm::vec3 Rotation = Constant::Vec3::Zero;
  glm::vec3 Scale = Constant::Vec3::One;
  glm::vec3 Forward = Constant::Vec3::Forward;
  glm::vec3 Right = Constant::Vec3::Right;
  glm::vec3 Up = Constant::Vec3::Up;
};

#endif // COSMOS_TRANSFORMCOMPONENT_H
