//
// Created by Echo on 2023/10/6.
//

#ifndef COSMOS_CONCEPTS_H
#define COSMOS_CONCEPTS_H
#include <utility>

class GameObject;
class Component;

template <typename T>
concept IsGameObject = std::is_base_of_v<GameObject, T>;

template <typename T>
concept IsComponent = std::is_base_of_v<Component, T>;

#endif // COSMOS_CONCEPTS_H
