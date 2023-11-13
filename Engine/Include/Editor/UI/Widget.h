/**
 * @file Widget.h
 * @author Echo
 * @Date 2023/10/7
 * @brief
 */

#ifndef COSMOS_WIDGET_H
#define COSMOS_WIDGET_H

#include "Core/Log/Logger.h"

#include <string>
#include <utility>
#include <vector>

class BaseUIElement;

namespace Editor {
class Widget {
public:
  explicit Widget(const std::string &name = "Widget");
  virtual void RenderGUI();
  /** 渲染EditorU前的准备工作,必须调用ImGui::Begin */
  virtual void BeginGUIRender();
  /** 渲染EditorU后的收尾工作,必须调用ImGui::End */
  virtual void EndGUIRender();

  virtual ~Widget();

  template <typename ElementType, typename... Args>
  requires std::is_base_of_v<BaseUIElement, ElementType>
  ElementType *AddElement(Args... args) {
    ElementType *element = new ElementType(std::forward<Args>(args)...);
    LOG_INFO("Base:{}", std::is_base_of_v<BaseUIElement, ElementType>)
    m_elements.push_back(element);
    return element;
  }

  std::string GetName() const { return m_name; }
  void SetName(std::string name) { m_name = std::move(name); }

protected:
  virtual void ConstructUIElements() {}

  std::string m_name;
  std::vector<BaseUIElement *> m_elements;
};
} // namespace Editor

#endif // COSMOS_WIDGET_H
