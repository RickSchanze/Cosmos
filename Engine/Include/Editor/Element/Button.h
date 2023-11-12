/**
 * @file Button.h
 * @author Echo 
 * @Date 2023/11/13
 * @brief 
 */

#ifndef BUTTON_H
#define BUTTON_H
#include "BaseUIElement.h"
#include "Core/Base/EventSystem.h"

enum class ButtonSizePolicy {
  Center,
  Left,
  Right
};

class Button : BaseUIElement {
public:
  explicit Button(const std::string &button_content, bool float_ = false);

  Event<> ButtonClickedEvent;

  // TODO: 完善此函数,让Button支持浮动、左右对齐和居中对齐
  void Render() override;

  void SetFloat(const bool is_float) { m_float = is_float; }
  bool IsFloat() const { return m_float; }

private:
  /** 这个Button是否能浮在其他元素上面 */
  bool m_float = false;
  std::string m_button_content;
};


#endif //BUTTON_H
