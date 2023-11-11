/**
 * @file SceneViewWidget.h
 * @author Echo
 * @Date 2023/10/7
 * @brief 自定义ImGui组件，目的是将OpenGL的渲染结果显示到这个组件中
 */

#ifndef COSMOS_SCENEVIEWWIDGET_H
#define COSMOS_SCENEVIEWWIDGET_H
#include "Function/Event/KeyEvent.h"
#include "Function/Event/MouseEvent.h"
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

// 这是一个比较特殊的Widget，因为需要管理Level里物体的渲染
class SceneViewWidget : public Widget {
public:
  explicit SceneViewWidget(std::string name = "SceneViewWidget");
  SceneViewWidget(int width, int height, std::string name = "SceneViewWidget");
  ~SceneViewWidget();

  void TakeInputKeyDown(KeyDownEventParams event);
  void TakeInputKeyUp(KeyReleasedEventParams event);
  void TakeInputKeyPressed(KeyPressedEventParams event);
  void TakeMouseMoveEvent(MouseMoveEventParams event);

  // 这里仅渲染GUI
  void Render() override;

  void TickRender();

  void TickLogic();

  void TickEndFrame();

  void BeginPlay();

  void EndPlay();

  inline void SetClearColor(const ImVec4 &color) { m_clear_color = color; }

  void BeginRender();

  void EndRender();

private:
  FrameBufferObject *m_frame_buffer_object;
  ImVec4 m_clear_color{1.f, 0.55f, 0.60f, 1.0f};
  std::string m_name;
  Level *m_level;
  GameObject *m_camera_object{};
  CameraComponent *m_camera_component{};

public:
  [[nodiscard]] inline Level *GetLevel() const { return m_level; }
  [[nodiscard]] inline CameraComponent* GetMainCamera() const { return m_camera_component; }

private:
  std::shared_ptr<VertexBufferObject> m_test_vbo;
  std::shared_ptr<VertexArrayObject> m_test_vao;
  std::shared_ptr<Shader> m_shader;

  float m_test_vertices[180] = {
      // positions          // texture Coords
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
      0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f, -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

      -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
      0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
      0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

      -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f};
};

} // namespace Editor

#endif // COSMOS_SCENEVIEWWIDGET_H
