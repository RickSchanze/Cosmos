//
// Created by Echo on 2023/10/5.
//

#ifndef COSMOS_COMPONENT_H
#define COSMOS_COMPONENT_H
#include "Core/Base/Object.h"
#include "Function/Event/KeyEvent.h"
#include "Function/Event/MouseEvent.h"

class GameObject;

class Component : public Object {
  friend class GameObject;

public:
  explicit Component(GameObject *owner) : m_owner_object(owner) {}

  virtual ~Component() = default;

public:
  // Tick顺序: TickLogic->TickRender->TickEndFrame
  // 渲染时发生的操作
  virtual void TickRender() {}
  // 渲染逻辑时的操作
  virtual void TickLogic() {}
  // 帧结束时的操作
  virtual void TickEndFrame() {}

  virtual void BeginPlay() {}

  virtual void EndPlay() {}

  virtual void TakeInputKeyDown(KeyDownEventParams event) {}
  virtual void TakeInputKeyUp(KeyReleasedEventParams event) {}
  virtual void TakeInputKeyPressed(KeyPressedEventParams event) {}
  virtual void TakeMouseMoveEvent(MouseMoveEventParams event) {}

public:
  GameObject *GetOwner() const { return m_owner_object; }

protected:
  bool m_enabled = true;
  GameObject *m_owner_object{};
};

#endif // COSMOS_COMPONENT_H
