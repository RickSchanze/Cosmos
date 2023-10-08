//
// Created by Echo on 2023/10/5.
//

#include "Function/GameObject.h"
#include "Function/Component/Component.h"
#include "Function/Component/TransformComponent.h"
#include "Function/Level.h"

GameObject::GameObject(Level *owner) : m_owner_level(owner) { m_transform = new TransformComponent(this); }

void GameObject::EndPlay() {
  for (auto &component : m_components) {
    component->EndPlay();
  }
}

void GameObject::BeginPlay() {
  for (auto &component : m_components) {
    component->BeginPlay();
  }
}

GameObject::~GameObject() {
  delete m_transform;
  for (auto &component : m_components) {
    component->EndPlay();
    delete component;
  }
}

void GameObject::SetOwnerLevel(Level *level) {
  m_owner_level = level;
  m_owner_level->AddGameObject(this);
}

void GameObject::TickEndFrame() {
  for (auto &component : m_components) {
    component->TickEndFrame();
  }
}

void GameObject::TickRender() {
  for (auto &component : m_components) {
    component->TickRender();
  }
}

void GameObject::TickLogic() {
  for (auto &component : m_components) {
    component->TickLogic();
  }
}

template <typename T>
requires IsComponent<T>
bool GameObject::RemoveComponent() {
  for (auto it = m_components.begin(); it != m_components.end(); ++it) {
    if (dynamic_cast<T *>(*it)) {
      (*it)->EndPlay();
      delete *it;
      m_components.erase(it);
      return true;
    }
  }
  return false;
}

template <typename T>
requires IsComponent<T>
T *GameObject::AddComponent() {
  T *component = new T(this);
  component->BeginPlay();
  m_components.push_back(component);
  return component;
}
