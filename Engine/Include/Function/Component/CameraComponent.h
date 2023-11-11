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

/**
 * Camera是个抽象的概念,本质上就是对物体做一系列变换
 * 从而将物体的坐标系变换到观察者的坐标系
 */
class CameraComponent : public Component {
public:
  explicit CameraComponent(GameObject *owner) : Component(owner) {}

  /** 获取观察矩阵 使用LookAt计算 */
  [[nodiscard]] glm::mat4 GetViewMatrix() const;

  /** 获取投影矩阵 */
  [[nodiscard]] glm::mat4 GetProjectionMatrix() const;

public:
  virtual void TickLogic() override;
  virtual void TakeInputKeyDown(KeyDownEventParams event) override;
  virtual void TakeInputKeyPressed(KeyPressedEventParams event) override;
  virtual void TakeMouseMoveEvent(MouseMoveEventParams event) override;

private:
  void UpdateCameraVectors();

private:
  // 欧拉角
  float m_yaw = -90.f;
  float m_pitch = 0.f;

public:
  // 相机参数
  float MovementSpeed = 0.1f;
  float MouseSensitivity = 0.01f;
  float Zoom = 45.0f;
  bool EnableInput = false;
};

#endif // COSMOS_CAMERACOMPONENT_H
