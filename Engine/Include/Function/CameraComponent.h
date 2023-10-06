//
// Created by Echo on 2023/10/6.
//

#ifndef COSMOS_CAMERACOMPONENT_H
#define COSMOS_CAMERACOMPONENT_H
#include "Component.h"

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
private:
public:
  float MovementSpeed = 2.5f;
  float MouseSensitivity = 0.1f;
  float Zoom = 45.0f;
};

#endif // COSMOS_CAMERACOMPONENT_H
