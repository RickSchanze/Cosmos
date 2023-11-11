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
struct KeyPressedEventParams {
public:
  explicit KeyPressedEventParams(KeyCode key_code) :Key(key_code) {}
  KeyPressedEventParams(const KeyPressedEventParams &event) { Key = event.Key; };

  KeyCode Key;
};

/**
 * 键盘释放事件，只在释放时触发一次
 */
struct KeyReleasedEventParams {
public:
  explicit KeyReleasedEventParams(KeyCode key_code): Key(key_code) {}
  KeyReleasedEventParams(const KeyReleasedEventParams &event) { Key = event.Key; };

  KeyCode Key;
};

/**
 * 键盘按下事件，只要按下就会触发
 */
struct KeyDownEventParams : public Event<KeyCode> {
public:
  explicit KeyDownEventParams(KeyCode key_code) : Event(), Key(key_code) {}
  KeyDownEventParams(const KeyDownEventParams &event) { Key = event.Key; };

  KeyCode Key;
};

#endif // COSMOS_KEYEVENT_H
