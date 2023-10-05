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
public:
  inline glm::vec3 GetForward() const { return m_forward; }
  inline glm::vec3 GetUp() const { return m_up; }

private:
  glm::vec3 m_forward;
  glm::vec3 m_up;

public:
  glm::vec3 Position = Constant::Zero;
  glm::vec3 Rotation = Constant::Zero;
  glm::vec3 Scale = Constant::One;
};

#endif // COSMOS_TRANSFORMCOMPONENT_H
