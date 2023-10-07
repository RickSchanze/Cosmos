/**
 * @file UIEvents.h
 * @author Echo
 * @Date 2023/10/7
 * @brief
 */

#ifndef COSMOS_UIEVENTS_H
#define COSMOS_UIEVENTS_H
#include "Core/Base/EventSystem.h"
#include "imgui.h"

class UIEvents {
public:
  static inline Event<ImVec4> OnClearColorChange;
};

#endif // COSMOS_UIEVENTS_H
