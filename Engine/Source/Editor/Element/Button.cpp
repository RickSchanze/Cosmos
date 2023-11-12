/**
 * @file Button.cpp
 * @author Echo
 * @Date 2023/11/13
 * @brief
 */

#include "Editor/Element/Button.h"

#include <imgui.h>

Button::Button(const std::string &button_content, bool float_) : m_button_content(button_content), m_float(float_) {}

void Button::Render() {
  if (m_float) {
    ImGui::SetItemAllowOverlap();
    ImGui::SetCursorPos(ImGui::GetWindowContentRegionMin());
  }
  if (ImGui::Button(m_button_content.c_str())) {
    ButtonClickedEvent.Dispatch();
  }
}
