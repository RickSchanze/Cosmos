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
  static inline Event<KeyPressedEventParams> KeyPressedEvent;
  static inline Event<KeyReleasedEventParams> KeyReleasedEvent;
  static inline Event<KeyDownEventParams> KeyDownEvent;
  static inline Event<MouseMoveEventParams> MouseMoveEvent;
};

#endif // COSMOS_GAMEEVENT_H
