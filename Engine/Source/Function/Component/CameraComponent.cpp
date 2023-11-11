//
// Created by Echo on 2023/10/6.
//

#include "Function/Component/CameraComponent.h"
#include "Core/Base/MathTypes.h"
#include "Function/Component/TransformComponent.h"
#include "Function/GameObject.h"

#include "Core/Log/Logger.h"
#include "Function/Event/GameEvent.h"
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

void CameraComponent::TickLogic() { UpdateCameraVectors(); }

void CameraComponent::TakeInputKeyDown(KeyDownEventParams event) {
  if (!EnableInput) return;
  auto *transform = m_owner_object->GetTransform();
  if (event.Key == KeyCode::W) {
    transform->Position += transform->Forward * MovementSpeed;
  }
  if (event.Key == KeyCode::S) {
    transform->Position -= transform->Forward * MovementSpeed;
  }
  // A和D可能有些问题 可能需要叉乘
  if (event.Key == KeyCode::A) {
    transform->Position -= transform->Right * MovementSpeed;
  }
  if (event.Key == KeyCode::D) {
    transform->Position += transform->Right * MovementSpeed;
  }
}

void CameraComponent::TakeMouseMoveEvent(MouseMoveEventParams event) {
  if (!EnableInput) return;
  {
    float x_offset = event.X;
    float y_offset = event.Y;
    m_yaw += x_offset * MouseSensitivity;
    m_pitch += -y_offset * MouseSensitivity;
    if (m_pitch > 89.0f) {
      m_pitch = 89.0f;
    }
    if (m_pitch < -89.0f) {
      m_pitch = -89.0f;
    }
  }
}

void CameraComponent::TakeInputKeyPressed(KeyPressedEventParams event) {
  if (!EnableInput) return;
  if (event.Key == KeyCode::Escape) {
    GameEvent::MouseLockEvent.Dispatch(false);
    EnableInput = false;
  }
}
