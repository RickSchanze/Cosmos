//
// Created by Echo on 2023/10/5.
//

#ifndef COSMOS_GAMEOBJECT_H
#define COSMOS_GAMEOBJECT_H
#include "Concepts.h"
#include "Core/Base/Object.h"

#include <string>
#include <vector>

class TransformComponent;
class Component;
class Level;

class GameObject : public Object {
  friend class Level;

public:
  explicit GameObject(Level *owner);
  ~GameObject();

  [[nodiscard]] TransformComponent *GetTransform() const { return m_transform; }

  template <typename T>
  requires IsComponent<T>
  T *AddComponent();

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

private:
  TransformComponent *m_transform;
  std::vector<Component *> m_components;
  std::string m_name;
  Level *m_owner_level;
};

#endif // COSMOS_GAMEOBJECT_H
