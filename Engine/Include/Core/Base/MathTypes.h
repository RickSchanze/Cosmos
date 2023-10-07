//
// Created by Echo on 2023/10/5.
//

#ifndef COSMOS_MATHTYPES_H
#define COSMOS_MATHTYPES_H
#include "glm/glm.hpp"
#include "imgui.h"

static glm::vec3 ToVec3(const ImVec4 &vec4) { return {vec4.x, vec4.y, vec4.z}; }

static glm::vec2 ToVec2(const ImVec2 &vec2) { return {vec2.x, vec2.y}; }

static ImVec4 ToImVec4(const glm::vec3 &vec3) { return {vec3.x, vec3.y, vec3.z, 1.f}; }

static ImVec4 ToImVec4(const glm::vec4 &vec4) { return {vec4.x, vec4.y, vec4.z, vec4.w}; }

static ImVec2 ToImVec2(const glm::vec2 &vec2) { return {vec2.x, vec2.y}; }

namespace Constant::Vec3 {

static glm::vec3 Zero = {0, 0, 0};
static glm::vec3 One = {1, 1, 1};
static glm::vec3 Up = {0, 1, 0};
static glm::vec3 Down = {0, -1, 0};
static glm::vec3 Left = {-1, 0, 0};
static glm::vec3 Right = {1, 0, 0};
static glm::vec3 Forward = {0, 0, 1};
static glm::vec3 Backward = {0, 0, -1};

} // namespace Constant::Vec3

namespace Constant::Mat4 {

static glm::mat4 Identity = glm::mat4(1.f);
static glm::mat4 Zero = glm::mat4(0.f);

} // namespace Constant::Mat4

#endif // COSMOS_MATHTYPES_H
