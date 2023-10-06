//
// Created by Echo on 2023/10/5.
//

#include "Function/GameObject.h"
#include "Function/Component.h"
#include "Function/Level.h"
#include "Function/TransformComponent.h"

GameObject::GameObject() { m_transform = new TransformComponent(this); }

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

void GameObject::Tick() {
  for (auto &component : m_components) {
    component->Tick();
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

template <typename T> requires IsComponent<T>
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

template <typename T> requires IsComponent<T>
T *GameObject::AddComponent() {
  T *component = new T(this);
  component->BeginPlay();
  m_components.push_back(component);
  return component;
}
