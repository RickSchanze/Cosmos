/**
 * @file KeyEvent.h
 * @author Echo
 * @Date 2023/10/7
 * @brief
 */

#ifndef COSMOS_KEYEVENT_H
#define COSMOS_KEYEVENT_H
#include "Core/Base/EventSystem.h"

enum class KeyCode { A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, Escape, Space };

struct KeyPressedEvent : public Event<KeyCode> {
public:
  explicit KeyPressedEvent(KeyCode key_code) : Event() {}

  KeyCode Key;
};

struct KeyReleasedEvent : public Event<KeyCode> {
public:
  explicit KeyReleasedEvent(KeyCode key_code) : Event() {}

  KeyCode Key;
};
#endif // COSMOS_KEYEVENT_H
