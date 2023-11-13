/**
 * @file Button.cpp
 * @author Echo
 * @Date 2023/11/13
 * @brief
 */

#include "Editor/Element/Button.h"

#include <imgui.h>

Button::Button(const std::string &label, const bool float_, const ButtonSizePolicy policy, const float alignment)
    : m_label(label), m_float(float_), m_size_policy(policy), m_alignment(alignment) {}


void Button::Render() {
  if (m_float) {
    ImGui::SetItemAllowOverlap();
    ImGui::SetCursorPos(ImGui::GetWindowContentRegionMin());
  }
  bool button_clicked = false;
  switch (m_size_policy) {
  case ButtonSizePolicy::Center:
    m_alignment = 0.5f;
    break;
  case ButtonSizePolicy::Left:
    m_alignment = 0.0f;
    break;
  case ButtonSizePolicy::Right:
    m_alignment = 1.0f;
    break;
  case ButtonSizePolicy::Custom:
    break;
  }
  if (ButtonOnLine(m_alignment)) {
    ButtonClickedEvent.Dispatch();
  }
}

bool Button::ButtonOnLine(const float alignment) {
  const ImGuiStyle &style = ImGui::GetStyle();
  const float size = ImGui::CalcTextSize(m_label.c_str()).x + style.FramePadding.x * 2.0f;
  const float avail = ImGui::GetContentRegionAvail().x;
  if (const float off = (avail - size) * alignment; off > 0.0f)
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);
  return ImGui::Button(m_label.c_str());
}
