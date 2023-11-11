/**
 * @file KeyEventHelper.h
 * @author Echo
 * @Date 2023/10/7
 * @brief
 */

#ifndef COSMOS_KEYEVENTHELPER_H
#define COSMOS_KEYEVENTHELPER_H

#include "KeyEvent.h"

class KeyEventHelper {
public:
  // 将ImGui key或GLFW_Key转换为KeyCode
  static KeyCode GetKeyCode(int key);

  // 将KeyCode转换为字符串
  static std::string GetKeyString(KeyCode key);
};
#endif // COSMOS_KEYEVENTHELPER_H
