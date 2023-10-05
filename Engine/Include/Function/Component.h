//
// Created by Echo on 2023/10/5.
//

#ifndef COSMOS_COMPONENT_H
#define COSMOS_COMPONENT_H
#include "Core/Base/Object.h"

class GameObject;

class Component : public Object {
public:
  virtual ~Component() = default;

protected:
  virtual void Tick() {}

  virtual void BeginPlay() {}

  virtual void EndPlay() {}

public:
  GameObject *OwnerObject{};

private:
  bool m_enabled = true;
};

#endif // COSMOS_COMPONENT_H
