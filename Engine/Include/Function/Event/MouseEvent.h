/**
 * @file KeyEvent.h
 * @author Echo
 * @Date 2023/10/7
 * @brief
 */

#ifndef COSMOS_MOUSEEVENT_H
#define COSMOS_MOUSEEVENT_H
#include "Core/Base/EventSystem.h"
#include "KeyCode.h"

struct MouseMoveEventParams {
  MouseMoveEventParams(float x, float y) : X(x), Y(y) {}
  MouseMoveEventParams(const MouseMoveEventParams &event) {
    X = event.X;
    Y = event.Y;
  }
  MouseMoveEventParams(double x, double y) : X(x), Y(y) {}

  float X;
  float Y;
};

#endif // COSMOS_MOUSEEVENT_H
