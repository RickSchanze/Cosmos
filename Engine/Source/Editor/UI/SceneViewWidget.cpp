/**
 * @file SceneViewWidget.cpp
 * @author Echo
 * @Date 2023/10/7
 * @brief
 */

#include <utility>

#include "Core/Log/Logger.h"
#include "Editor/Events/UIEvents.h"
#include "Editor/UI/SceneViewWidget.h"
#include "Function/Component/CameraComponent.h"
#include "Function/Event/GameEvent.h"
#include "Function/GameObject.h"
#include "Function/Level.h"
#include "Global/GlobalDefiniation.h"
#include "Platform/OpenGL/FrameBufferObject.h"
#include "Platform/OpenGL/Shader.h"
#include "Platform/OpenGL/VertexArrayObject.h"
#include "Platform/OpenGL/VertexBufferObject.h"
#include "glad/glad.h"

Editor::SceneViewWidget::SceneViewWidget(int width, int height, std::string name) : SceneViewWidget(std::move(name)) {}

Editor::SceneViewWidget::SceneViewWidget(std::string name) : m_name(std::move(name)) {
  m_frame_buffer_object = new FrameBufferObject(1920, 1080);
  UIEvents::OnClearColorChange.AddEventListener("GlobalClearColorChanged", this, &SceneViewWidget::SetClearColor);
  GameEvent::OnKeyDown.AddEventListener("SceneViewWidget_KeyDown", this, &SceneViewWidget::TakeInputKeyDown);
  GameEvent::OnKeyReleased.AddEventListener("SceneViewWidget_KeyReleased", this, &SceneViewWidget::TakeInputKeyUp);
  GameEvent::OnKeyPressed.AddEventListener("SceneViewWidget_KeyPressed", this, &SceneViewWidget::TakeInputKeyPressed);
  GameEvent::OnMouseMove.AddEventListener("SceneViewWidget_MouseMove", this, &SceneViewWidget::TakeMouseMoveEvent);
  m_level = new Level();
}

Editor::SceneViewWidget::~SceneViewWidget() {
  delete m_frame_buffer_object;
  delete m_level;
  UIEvents::OnClearColorChange.RemoveEventListener("GlobalClearColorChanged");
  GameEvent::OnKeyDown.RemoveEventListener("SceneViewWidget_KeyDown");
  GameEvent::OnKeyReleased.RemoveEventListener("SceneViewWidget_KeyReleased");
  GameEvent::OnKeyPressed.RemoveEventListener("SceneViewWidget_KeyPressed");
  GameEvent::OnMouseMove.RemoveEventListener("SceneViewWidget_MouseMove");
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

void Editor::SceneViewWidget::TickLogic() {
  m_camera_object->TickLogic();
  m_level->TickLogic();
}

void Editor::SceneViewWidget::TickRender() {
  m_camera_object->TickRender();
  m_level->TickRender();
  glm::mat4 projection = m_camera_component->GetProjectionMatrix();
  glm::mat4 view = m_camera_component->GetViewMatrix();
  m_shader->Use();
  m_shader->SetMatrix4f("model", glm::mat4(1.0f));
  m_shader->SetMatrix4f("view", view);
  m_shader->SetMatrix4f("projection", projection);
  m_test_vao->Bind();
  glDrawArrays(GL_TRIANGLES, 0, 6);
  m_test_vao->Unbind();
}

void Editor::SceneViewWidget::EndPlay() { m_level->EndPlay(); }

void Editor::SceneViewWidget::BeginPlay() {
  // 添加摄像机组件
  m_camera_object = new GameObject("MainCamera");
  m_camera_component = m_camera_object->AddComponent<CameraComponent>();
  m_level->BeginPlay();
  m_test_vao = std::make_shared<VertexArrayObject>();
  m_test_vbo = std::make_shared<VertexBufferObject>(DataLayoutOfVbo::Position, DataLayoutOfVbo::Normal);
  m_test_vao->Bind();
  m_test_vbo->Bind();
  m_test_vbo->SetData(m_test_vertices, sizeof(m_test_vertices));
  m_test_vao->AttributeVBO(*m_test_vbo, 6 * sizeof(float));
  m_shader = std::make_shared<Shader>(COSMOS_SHADER_PATH "/test.vert", COSMOS_SHADER_PATH "/test.frag");
}

void Editor::SceneViewWidget::TakeInputKeyDown(KeyDownEvent event) {
  m_camera_object->TakeInputKeyDown(event);
  m_level->TakeInputKeyDown(event);
}

void Editor::SceneViewWidget::TakeInputKeyUp(KeyReleasedEvent event) {
  m_camera_object->TakeInputKeyUp(event);
  m_level->TakeInputKeyUp(event);
}
void Editor::SceneViewWidget::TakeInputKeyPressed(KeyPressedEvent event) {
  m_camera_object->TakeInputKeyPressed(event);
  m_level->TakeInputKeyPressed(event);
}
void Editor::SceneViewWidget::TakeMouseMoveEvent(MouseMoveEvent event) {
  m_camera_object->TakeMouseMoveEvent(event);
  m_level->TakeMouseMoveEvent(event);
}
