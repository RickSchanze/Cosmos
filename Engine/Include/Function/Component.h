//
// Created by Echo on 2023/10/5.
//

#ifndef COSMOS_COMPONENT_H
#define COSMOS_COMPONENT_H
#include "Core/Base/Object.h"

class GameObject;

class Component : public Object {
  friend class GameObject;

public:
  explicit Component(GameObject *owner) : m_owner_object(owner) {}

  virtual ~Component() = default;

protected:
  virtual void Tick() {}

  virtual void BeginPlay() {}

  virtual void EndPlay() {}

public:
  GameObject *GetOwner() const { return m_owner_object; }

protected:
  bool m_enabled = true;
  GameObject *m_owner_object{};
};

#endif // COSMOS_COMPONENT_H
