/**
 * @file DebugWidget.cpp
 * @author Echo
 * @Date 2023/10/7
 * @brief
 */

#include "Editor/UI/DebugWidget.h"
#include "Editor/Events/UIEvents.h"
#include "imgui.h"

void Editor::DebugWidget::Render() {
  ImGui::Begin(m_name.c_str());
  ImGui::ColorEdit4("clear color", &m_clear_color.x);
  ImGui::End();
  UIEvents::OnClearColorChange.Invoke(m_clear_color);
}

Editor::DebugWidget::DebugWidget(const std::string &name) { m_name = name; }
