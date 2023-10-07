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
namespace Editor {

class SceneViewWidget : public Widget {
public:
  explicit SceneViewWidget(std::string name = "SceneViewWidget");
  SceneViewWidget(int width, int height, std::string name = "SceneViewWidget");
  ~SceneViewWidget();

  // 单纯渲染Editor UI
  void Render() override;

  // 这个是为了让Application调用Render用的
  // 为了能让渲染出的图像显示在这个Widget上，就必须先Bind然后Unbind
  void BeginRender();

  void EndRender();

  inline void SetClearColor(const ImVec4 &color) { m_clear_color = color; }

private:
  FrameBufferObject *m_frame_buffer_object;
  ImVec4 m_clear_color{1.f, 0.55f, 0.60f, 1.0f};
  std::string m_name;
};

} // namespace Editor

#endif // COSMOS_SCENEVIEWWIDGET_H
