//
// Created by Echo on 2023/10/5.
//

#ifndef COSMOS_GAMEOBJECT_H
#define COSMOS_GAMEOBJECT_H
#include "Core/Base/Object.h"

class TransformComponent;

class GameObject : public Object {

public:
  TransformComponent *Transform;
};

#endif // COSMOS_GAMEOBJECT_H
