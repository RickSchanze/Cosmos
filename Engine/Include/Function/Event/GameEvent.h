/**
 * @file GameEvent.h
 * @author Echo
 * @Date 2023/10/7
 * @brief
 */

#ifndef COSMOS_GAMEEVENT_H
#define COSMOS_GAMEEVENT_H
#include "Core/Base/EventSystem.h"
#include "KeyEvent.h"
#include "MouseEvent.h"

class GameEvent {
public:
  static inline Event<KeyPressedEvent> OnKeyPressed;
  static inline Event<KeyReleasedEvent> OnKeyReleased;
  static inline Event<KeyDownEvent> OnKeyDown;
  static inline Event<MouseMoveEvent> OnMouseMove;
};

#endif // COSMOS_GAMEEVENT_H
