/**
 * @file SceneViewWidget.h
 * @author Echo
 * @Date 2023/10/7
 * @brief 自定义ImGui组件，目的是将OpenGL的渲染结果显示到这个组件中
 */

#ifndef COSMOS_SCENEVIEWWIDGET_H
#define COSMOS_SCENEVIEWWIDGET_H
#include "Editor/Element/Button.h"
#include "Function/Event/KeyEvent.h"
#include "Function/Event/MouseEvent.h"
#include "Platform/OpenGL/Texture.h"
#include "Widget.h"
#include "imgui.h"

#include <memory>
#include <string>

class FrameBufferObject;
class Level;
class VertexBufferObject;
class VertexArrayObject;
class Shader;
class GameObject;
class CameraComponent;

namespace Editor {

/**
 * @brief 这是一个比较特殊的Widget，因为需要管理Level里物体的渲染
 * TODO: 终极目标是实现点击此view即可开始编辑,当前编辑/在场景内转动/移动视角需要点击按钮
 */
class SceneViewWidget : public Widget {
public:
  explicit SceneViewWidget(const std::string &name = "SceneViewWidget");
  ~SceneViewWidget();

  void TakeInputKeyDown(KeyDownEventParams event);
  void TakeInputKeyUp(KeyReleasedEventParams event);
  void TakeInputKeyPressed(KeyPressedEventParams event);
  void TakeMouseMoveEvent(MouseMoveEventParams event);

  // 这里仅渲染GUI
  void RenderGUI() override;

  void TickRender();

  void TickLogic();

  void TickEndFrame();

  void BeginPlay();

  void EndPlay();

  void SetClearColor(const ImVec4 &color) { m_clear_color = color; }

  void BeginRender();

  void EndRender();

protected:
  void OnBeginButtonClicked();
  /** UI元素 */
  Button *m_button_focus;

private:
  FrameBufferObject *m_frame_buffer_object;
  ImVec4 m_clear_color{1.f, 0.55f, 0.60f, 1.0f};
  Level *m_level;
  GameObject *m_camera_object{};
  CameraComponent *m_camera_component{};
  bool m_focused;

public:
  Level *GetLevel() const { return m_level; }
  CameraComponent *GetMainCamera() const { return m_camera_component; }
};

} // namespace Editor

#endif // COSMOS_SCENEVIEWWIDGET_H
