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

enum class ButtonSizePolicy { Center, Left, Right, Custom };

class Button : public BaseUIElement {
public:
  explicit Button(const std::string &label, bool float_ = false, ButtonSizePolicy policy = ButtonSizePolicy::Center, float alignment = 0.5f);
  Event<> ButtonClickedEvent;

  void Render() override;

  void SetFloat(const bool is_float) { m_float = is_float; }
  bool IsFloat() const { return m_float; }

protected:
  /**
   * \brief 绘制一个Button alignment是对齐的比例
   * \param alignment
   * \return
   */
  bool ButtonOnLine(float alignment = 0.5f);

private:


  /** 这个Button是否能浮在其他元素上面 */
  bool m_float = false;
  std::string m_label;
  ButtonSizePolicy m_size_policy = ButtonSizePolicy::Center;
  float m_alignment = 0.5f;
};


#endif //BUTTON_H
