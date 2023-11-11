/**
 * @file DebugWidget.cpp
 * @author Echo
 * @Date 2023/10/7
 * @brief
 */

#include "Editor/UI/DebugWidget.h"
#include "Editor/Application.h"
#include "Editor/Events/UIEvents.h"
#include "Editor/UI/SceneViewWidget.h"
#include "Function/Component/CameraComponent.h"
#include "imgui.h"

void Editor::DebugWidget::Render() {
  ImGui::Begin(m_name.c_str());
  ImGui::ColorEdit4("clear color", &m_clear_color.x);
  ImGui::SliderFloat("camera speed", &m_camera_speed, 0.0f, 5.f);
  ImGui::SliderFloat("mouse sensitive", &m_sensitive, 0.0f, 3.0f);
  ImGui::End();
  UIEvents::OnClearColorChange.Dispatch(m_clear_color);
  if (Application::GetApplication() && Application::GetApplication()->GetMainSceneViewWidget()) {
    auto *main_camera = Application::GetApplication()->GetMainSceneViewWidget()->GetMainCamera();
    if (main_camera) {
      main_camera->MovementSpeed = m_camera_speed;
      main_camera->MouseSensitivity = m_sensitive;
    }
  }
}

Editor::DebugWidget::DebugWidget(const std::string &name) { m_name = name; }
