//
// Created by Echo on 2023/10/6.
//

#include "Function/Level.h"
#include "Function/GameObject.h"

void Level::AddGameObject(GameObject *game_object) {
  if (std::find(m_game_objects.begin(), m_game_objects.end(), game_object) == m_game_objects.end())
    return;
  m_game_objects.push_back(game_object);
}

bool Level::RemoveGameObject(GameObject *obj_ptr) {
  auto it = std::find(m_game_objects.begin(), m_game_objects.end(), obj_ptr);
  if (it != m_game_objects.end()) {
    m_game_objects.erase(it);
    delete obj_ptr;
    return true;
  }
  return false;
}

bool Level::RemoveGameObject(std::string obj_name) {
  auto it = std::find_if(m_game_objects.begin(), m_game_objects.end(),
                         [&obj_name](GameObject *obj) { return obj->GetName() == obj_name; });
  if (it != m_game_objects.end()) {
    m_game_objects.erase(it);
    delete *it;
    return true;
  }
  return false;
}

GameObject *Level::GetGameObject(std::string obj_name) {
  auto it = std::find_if(m_game_objects.begin(), m_game_objects.end(),
                         [&obj_name](GameObject *obj) { return obj->GetName() == obj_name; });
  if (it != m_game_objects.end()) {
    return *it;
  }
  return nullptr;
}

void Level::TickRender() {
  for (auto &game_object : m_game_objects) {
    game_object->TickRender();
  }
}

void Level::TickEndFrame() {
  for (auto &game_object : m_game_objects) {
    game_object->TickEndFrame();
  }
}

void Level::TickLogic() {
  for (auto &game_object : m_game_objects) {
    game_object->TickLogic();
  }
}

void Level::BeginPlay() {
  for (auto &game_object : m_game_objects) {
    game_object->BeginPlay();
  }
}

void Level::EndPlay() {
  for (auto &game_object : m_game_objects) {
    game_object->EndPlay();
  }
}
