//
// Created by Echo on 2023/10/6.
//

#ifndef COSMOS_CAMERACOMPONENT_H
#define COSMOS_CAMERACOMPONENT_H
#include "Component.h"
#include "glm/glm.hpp"

class GameObject;

enum class CameraMovement {
  Forward,  // 向前
  Backward, // 向后
  Left,     // 向左
  Right,    // 向右
  Up,       // 向上
  Down      // 向下
};

class CameraComponent : public Component {
public:
  explicit CameraComponent(GameObject *owner) : Component(owner) {}

  /** 获取观察矩阵 使用LookAt计算 */
  [[nodiscard]] glm::mat4 GetViewMatrix() const;

  /** 获取投影矩阵 */
  [[nodiscard]] glm::mat4 GetProjectionMatrix() const;

private:
  void UpdateCameraVectors();

private:
  // 欧拉角
  float m_yaw = -90.f;
  float m_pitch = 0.f;

public:
  // 相机参数
  float MovementSpeed = 2.5f;
  float MouseSensitivity = 0.1f;
  float Zoom = 45.0f;
};

#endif // COSMOS_CAMERACOMPONENT_H
