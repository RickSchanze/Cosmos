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
#include "Resource/Image.h"
#include "glad/glad.h"

Editor::SceneViewWidget::SceneViewWidget(const std::string &name) : Widget(name) {
  m_frame_buffer_object = new FrameBufferObject(1920, 1080);
  m_button_focus = AddElement<Button>("开始");
  if (m_button_focus) {
    m_button_focus->ButtonClickedEvent.AddEventListener("BeginButtonClicked", this, &SceneViewWidget::OnBeginButtonClicked);
  }
  UIEvents::OnClearColorChange.AddEventListener("GlobalClearColorChanged", this, &SceneViewWidget::SetClearColor);
  GameEvent::KeyDownEvent.AddEventListener("SceneViewWidget_KeyDown", this, &SceneViewWidget::TakeInputKeyDown);
  GameEvent::KeyReleasedEvent.AddEventListener("SceneViewWidget_KeyReleased", this, &SceneViewWidget::TakeInputKeyUp);
  GameEvent::KeyPressedEvent.AddEventListener("SceneViewWidget_KeyPressed", this, &SceneViewWidget::TakeInputKeyPressed);
  GameEvent::MouseMoveEvent.AddEventListener("SceneViewWidget_MouseMove", this, &SceneViewWidget::TakeMouseMoveEvent);
  m_level = new Level();
}

Editor::SceneViewWidget::~SceneViewWidget() {
  delete m_frame_buffer_object;
  delete m_level;
  UIEvents::OnClearColorChange.RemoveEventListener("GlobalClearColorChanged");
  GameEvent::KeyDownEvent.RemoveEventListener("SceneViewWidget_KeyDown");
  GameEvent::KeyReleasedEvent.RemoveEventListener("SceneViewWidget_KeyReleased");
  GameEvent::KeyPressedEvent.RemoveEventListener("SceneViewWidget_KeyPressed");
  GameEvent::MouseMoveEvent.RemoveEventListener("SceneViewWidget_MouseMove");
}

void Editor::SceneViewWidget::RenderGUI() {
  ImGui::Image(reinterpret_cast<ImTextureID>(m_frame_buffer_object->GetFBO()), ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
  ImGui::SetItemAllowOverlap();
  ImGui::SetCursorPos(ImGui::GetWindowContentRegionMin());
  Widget::RenderGUI();
}

void Editor::SceneViewWidget::BeginRender() {
  m_frame_buffer_object->Bind();
  glClearColor(m_clear_color.x, m_clear_color.y, m_clear_color.z, m_clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Editor::SceneViewWidget::EndRender() { m_frame_buffer_object->Unbind(); }

void Editor::SceneViewWidget::OnBeginButtonClicked() {
  GameEvent::MouseLockEvent.Dispatch(true);
  m_camera_component->EnableInput = true;
}

void Editor::SceneViewWidget::TickEndFrame() { m_level->TickEndFrame(); }

void Editor::SceneViewWidget::TickLogic() {
  m_camera_object->TickLogic();
  m_level->TickLogic();
}

void Editor::SceneViewWidget::TickRender() {
  m_camera_object->TickRender();
  m_level->TickRender();
  const glm::mat4 projection = m_camera_component->GetProjectionMatrix();
  const glm::mat4 view = m_camera_component->GetViewMatrix();
}

void Editor::SceneViewWidget::EndPlay() {
  m_level->EndPlay();
}

void Editor::SceneViewWidget::BeginPlay() {
  // 添加摄像机组件
  m_camera_object = new GameObject("MainCamera");
  m_camera_component = m_camera_object->AddComponent<CameraComponent>();
}

void Editor::SceneViewWidget::TakeInputKeyDown(KeyDownEventParams event) {
  m_camera_object->TakeInputKeyDown(event);
  m_level->TakeInputKeyDown(event);
}

void Editor::SceneViewWidget::TakeInputKeyUp(KeyReleasedEventParams event) {
  m_camera_object->TakeInputKeyUp(event);
  m_level->TakeInputKeyUp(event);
}
void Editor::SceneViewWidget::TakeInputKeyPressed(KeyPressedEventParams event) {
  m_camera_object->TakeInputKeyPressed(event);
  m_level->TakeInputKeyPressed(event);
}
void Editor::SceneViewWidget::TakeMouseMoveEvent(MouseMoveEventParams event) {
  m_camera_object->TakeMouseMoveEvent(event);
  m_level->TakeMouseMoveEvent(event);
}
