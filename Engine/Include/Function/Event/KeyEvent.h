/**
 * @file KeyEvent.h
 * @author Echo
 * @Date 2023/10/7
 * @brief
 */

#ifndef COSMOS_KEYEVENT_H
#define COSMOS_KEYEVENT_H
#include "Core/Base/EventSystem.h"
#include "KeyCode.h"

/**
 * 键盘按下事件，只在按下时触发一次
 */
struct KeyPressedEvent : public Event<KeyCode> {
public:
  explicit KeyPressedEvent(KeyCode key_code) : Event(), Key(key_code) {}
  KeyPressedEvent(const KeyPressedEvent &event) { Key = event.Key; };

  KeyCode Key;
};

/**
 * 键盘释放事件，只在释放时触发一次
 */
struct KeyReleasedEvent : public Event<KeyCode> {
public:
  explicit KeyReleasedEvent(KeyCode key_code) : Event(), Key(key_code) {}
  KeyReleasedEvent(const KeyReleasedEvent &event) { Key = event.Key; };

  KeyCode Key;
};

/**
 * 键盘按下事件，只要按下就会触发
 */
struct KeyDownEvent : public Event<KeyCode> {
public:
  explicit KeyDownEvent(KeyCode key_code) : Event(), Key(key_code) {}
  KeyDownEvent(const KeyDownEvent &event) { Key = event.Key; };

  KeyCode Key;
};

#endif // COSMOS_KEYEVENT_H
