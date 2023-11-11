/**
 * @file DebugWidget.h
 * @author Echo
 * @Date 2023/10/7
 * @brief
 */

#ifndef COSMOS_DEBUGWIDGET_H
#define COSMOS_DEBUGWIDGET_H
#include "Widget.h"
#include "imgui.h"

namespace Editor {
class DebugWidget : public Widget {
public:
  explicit DebugWidget(const std::string &name = "DebugWidget");
  ~DebugWidget() = default;

  void Render() override;

private:
  ImVec4 m_clear_color{0.45f, 0.55f, 0.60f, 1.0f};
  float m_camera_speed = 0.8f;
  float m_sensitive = 0.1f;
};
} // namespace Editor

#endif // COSMOS_DEBUGWIDGET_H
