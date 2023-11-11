//
// Created by Echo on 2023/10/5.
//

#ifndef COSMOS_GAMEOBJECT_H
#define COSMOS_GAMEOBJECT_H
#include "Concepts.h"
#include "Core/Base/Object.h"
#include "Function/Event/KeyEvent.h"
#include "Function/Event/MouseEvent.h"

#include <string>
#include <vector>

class TransformComponent;
class Component;
class Level;

namespace Editor {
class SceneViewWidget;
}

class GameObject : public Object {
  friend class Level;
  friend class Editor::SceneViewWidget;

public:
  explicit GameObject(Level *owner);
  explicit GameObject(Level *owner, std::string name);
  /**
   * 一定要将GameObject添加到Level中
   * 否则不会Tick这个Object
   * 还可能内存泄露
   * @param name
   */
  explicit GameObject(std::string name);
  ~GameObject();

  [[nodiscard]] TransformComponent *GetTransform() const { return m_transform; }

  template <typename T>
  requires IsComponent<T>
  T *AddComponent() {
    T *component = new T(this);
    component->BeginPlay();
    m_components.push_back(component);
    return component;
  }

  template <typename T>
  requires IsComponent<T>
  bool RemoveComponent();

  void SetOwnerLevel(Level *level);
  [[nodiscard]] inline Level *GetOwnerLevel() const { return m_owner_level; }

  [[nodiscard]] inline std::string GetName() const { return m_name; }
  inline void SetName(std::string name) { m_name = std::move(name); }

protected:
  void TickRender();

  void TickLogic();

  void TickEndFrame();

  void BeginPlay();

  void EndPlay();

  /**
   * 输入事件 转发给所有组件处理
   * @param event
   */
  void TakeInputKeyDown(KeyDownEventParams event);
  void TakeInputKeyUp(KeyReleasedEventParams event);
  void TakeInputKeyPressed(KeyPressedEventParams event);
  void TakeMouseMoveEvent(MouseMoveEventParams event);

private:
  TransformComponent *m_transform;
  std::vector<Component *> m_components;
  std::string m_name;
  Level *m_owner_level;
};

#endif // COSMOS_GAMEOBJECT_H
