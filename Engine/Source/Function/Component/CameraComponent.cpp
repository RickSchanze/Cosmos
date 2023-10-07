//
// Created by Echo on 2023/10/6.
//

#include "Function/Component/CameraComponent.h"
#include "Core/Base/MathTypes.h"
#include "Function/Component/TransformComponent.h"
#include "Function/GameObject.h"

#include "glm/gtc/matrix_transform.hpp"

glm::mat4 CameraComponent::GetProjectionMatrix() const {
  auto transform = m_owner_object->GetTransform();
  return glm::perspective(glm::radians(Zoom), transform->Scale.x / transform->Scale.y, 0.1f, 100.0f);
}

glm::mat4 CameraComponent::GetViewMatrix() const {
  auto transform = m_owner_object->GetTransform();
  return glm::lookAt(transform->Position, transform->Position + transform->Forward, transform->Up);
}

void CameraComponent::UpdateCameraVectors() {
  glm::vec3 front;
  front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
  front.y = sin(glm::radians(m_pitch));
  front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
  auto transform = m_owner_object->GetTransform();
  transform->Forward = glm::normalize(front);
  transform->Right = glm::normalize(glm::cross(transform->Forward, Constant::Vec3::Up));
  transform->Up = glm::normalize(glm::cross(transform->Right, transform->Forward));
}
