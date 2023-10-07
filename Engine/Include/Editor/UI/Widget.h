/**
 * @file Widget.h
 * @author Echo
 * @Date 2023/10/7
 * @brief
 */

#ifndef COSMOS_WIDGET_H
#define COSMOS_WIDGET_H
#include <string>
#include <utility>

namespace Editor {
class Widget {
public:
  virtual void Render() {}

  [[nodiscard]] inline std::string GetName() const { return m_name; }
  inline void SetName(std::string name) { m_name = std::move(name); }

protected:
  std::string m_name;
};
} // namespace Editor

#endif // COSMOS_WIDGET_H
