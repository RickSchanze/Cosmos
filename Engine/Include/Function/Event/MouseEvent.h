/**
 * @file KeyEvent.h
 * @author Echo
 * @Date 2023/10/7
 * @brief
 */

#ifndef COSMOS_MOUSEEVENT_H
#define COSMOS_MOUSEEVENT_H

struct MouseMoveEventParams {
  MouseMoveEventParams(const float x, const float y) : X(x), Y(y) {}
  MouseMoveEventParams(const MouseMoveEventParams &event) {
    X = event.X;
    Y = event.Y;
  }
  MouseMoveEventParams(const double x, const double y) : X(x), Y(y) {}

  float X;
  float Y;
};

#endif // COSMOS_MOUSEEVENT_H
