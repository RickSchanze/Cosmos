/**
 * @file SceneViewWidget.h
 * @author Echo
 * @Date 2023/10/7
 * @brief 自定义ImGui组件，目的是将OpenGL的渲染结果显示到这个组件中
 */

#ifndef COSMOS_SCENEVIEWWIDGET_H
#define COSMOS_SCENEVIEWWIDGET_H
#include "Widget.h"
#include "imgui.h"

#include <string>

class FrameBufferObject;
class Level;
class VertexBufferObject;
class VertexArrayObject;
class Shader;

namespace Editor {

// 这是一个比较特殊的Widget，因为需要管理Level里物体的渲染
class SceneViewWidget : public Widget {
public:
  explicit SceneViewWidget(std::string name = "SceneViewWidget");
  SceneViewWidget(int width, int height, std::string name = "SceneViewWidget");
  ~SceneViewWidget();

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

public:
  [[nodiscard]] inline Level *GetLevel() const { return m_level; }

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
