/**
 * @file SceneViewWidget.cpp
 * @author Echo
 * @Date 2023/10/7
 * @brief
 */

#include <utility>

#include "Editor/Events/UIEvents.h"
#include "Editor/UI/SceneViewWidget.h"
#include "Function/Level.h"
#include "Platform/OpenGL/FrameBufferObject.h"
#include "Platform/OpenGL/VertexArrayObject.h"
#include "Platform/OpenGL/VertexBufferObject.h"
#include "glad/glad.h"

Editor::SceneViewWidget::SceneViewWidget(int width, int height, std::string name) : SceneViewWidget(std::move(name)) {}

Editor::SceneViewWidget::SceneViewWidget(std::string name) : m_name(std::move(name)) {
  m_frame_buffer_object = new FrameBufferObject(1920, 1080);
  UIEvents::OnClearColorChange.AddEventListener("GlobalClearColorChanged", this, &SceneViewWidget::SetClearColor);
  m_level = new Level();
}

Editor::SceneViewWidget::~SceneViewWidget() {
  delete m_frame_buffer_object;
  delete m_level;
  UIEvents::OnClearColorChange.RemoveEventListener("GlobalClearColorChanged");
}

void Editor::SceneViewWidget::Render() {
  ImGui::Begin(m_name.c_str());
  ImGui::Image(reinterpret_cast<ImTextureID>(m_frame_buffer_object->GetFBO()), ImGui::GetContentRegionAvail(),
               ImVec2(0, 1), ImVec2(1, 0));
  ImGui::End();
}

void Editor::SceneViewWidget::BeginRender() {
  m_frame_buffer_object->Bind();
  glClearColor(m_clear_color.x, m_clear_color.y, m_clear_color.z, m_clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Editor::SceneViewWidget::EndRender() { m_frame_buffer_object->Unbind(); }

void Editor::SceneViewWidget::TickEndFrame() { m_level->TickEndFrame(); }

void Editor::SceneViewWidget::TickLogic() { m_level->TickLogic(); }

void Editor::SceneViewWidget::TickRender() { m_level->TickRender(); }

void Editor::SceneViewWidget::EndPlay() { m_level->EndPlay(); }

void Editor::SceneViewWidget::BeginPlay() { m_level->BeginPlay(); }
