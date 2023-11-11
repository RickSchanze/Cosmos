//
// Created by Echo on 2023/10/6.
//

#ifndef COSMOS_LEVEL_H
#define COSMOS_LEVEL_H
#include "Concepts.h"
#include "Function/Event/KeyEvent.h"
#include "Function/Event/MouseEvent.h"

#include <string>
#include <vector>

class GameObject;

class Level {
public:
  ~Level();

  std::vector<GameObject *> &GetGameObjects() { return m_game_objects; }

  /** 增加一个游戏对象 */
  void AddGameObject(GameObject *game_object);

  /** 删除游戏对象 */
  bool RemoveGameObject(GameObject *obj_ptr);

  /** 通过名字删除，删除时会调用Component的EndPlay */
  bool RemoveGameObject(std::string obj_name);

  /** 获得游戏对象指针 */
  GameObject *GetGameObject(std::string obj_name);

  void TickLogic();

  void TickRender();

  void TickEndFrame();

  void BeginPlay();

  void EndPlay();

  /**
   * 输入转发给GameObject然后转发给Component处理
   * @param event
   */
  void TakeInputKeyDown(KeyDownEvent event);
  void TakeInputKeyUp(KeyReleasedEvent event);
  void TakeInputKeyPressed(KeyPressedEvent event);
  void TakeMouseMoveEvent(MouseMoveEvent event);

private:
  std::vector<GameObject *> m_game_objects;
};

#endif // COSMOS_LEVEL_H
