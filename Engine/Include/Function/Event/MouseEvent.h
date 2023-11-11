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

struct MouseMoveEvent : public Event<float, float> {
  MouseMoveEvent(float x, float y) : X(x), Y(y) {}
  MouseMoveEvent(const MouseMoveEvent &event) {
    X = event.X;
    Y = event.Y;
  }
  MouseMoveEvent(double x, double y) : X(x), Y(y) {}

  float X;
  float Y;
};

#endif // COSMOS_MOUSEEVENT_H
