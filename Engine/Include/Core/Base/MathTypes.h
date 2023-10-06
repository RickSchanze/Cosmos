//
// Created by Echo on 2023/10/5.
//

#ifndef COSMOS_MATHTYPES_H
#define COSMOS_MATHTYPES_H
#include "glm/glm.hpp"
#include "imgui.h"

static glm::vec3 ToVec3(const ImVec4 &vec4) { return {vec4.x, vec4.y, vec4.z}; }

static glm::vec2 ToVec2(const ImVec2 &vec2) { return {vec2.x, vec2.y}; }

namespace Constant {

static glm::vec3 Zero = {0, 0, 0};
static glm::vec3 One = {1, 1, 1};
static glm::vec3 Up = {0, 1, 0};
static glm::vec3 Down = {0, -1, 0};
static glm::vec3 Left = {-1, 0, 0};
static glm::vec3 Right = {1, 0, 0};
static glm::vec3 Forward = {0, 0, 1};
static glm::vec3 Backward = {0, 0, -1};

} // namespace Constant

#endif // COSMOS_MATHTYPES_H
