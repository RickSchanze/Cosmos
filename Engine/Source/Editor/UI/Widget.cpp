/**
 * @file Widget.cpp
 * @author Echo
 * @Date 2023/10/7
 * @brief
 */

#include "Editor/UI/Widget.h"

#include "Editor/Element/BaseUIElement.h"

#include <imgui.h>
Editor::Widget::Widget(std::string name): m_name(name) {}
void Editor::Widget::RenderGUI() {
  for (const auto &element : m_elements) {
    element->Render();
  }
}
void Editor::Widget::BeginGUIRender() { ImGui::Begin(m_name.c_str()); }
void Editor::Widget::EndGUIRender() { ImGui::End(); }

Editor::Widget::~Widget() {
  for (const auto &element : m_elements) {
    delete element;
  }
}
