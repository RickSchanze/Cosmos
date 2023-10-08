/**
 * @file Shader.h
 * @author Echo
 * @Date 2023/10/8
 * @brief
 */

#ifndef COSMOS_SHADER_H
#define COSMOS_SHADER_H
#include "glm/ext/matrix_float4x4.hpp"
#include <cstdint>

class Shader {
public:
  Shader(const char *vert_shader_path, const char *frag_shader_path);

  void Use();

  void SetBool(const std::string &name, bool value) const;
  void SetInt(const std::string &name, int value) const;
  void SetUInt(const std::string &name, unsigned int value) const;
  void SetFloat(const std::string &name, float value) const;
  void SetMatrix4f(const std::string &name, const glm::mat4 &value) const;
  void SetVec3(const std::string &name, const glm::vec3 &value) const;

private:
  uint32_t m_id;
  const char *m_vert_shader_code;
  const char *m_frag_shader_code;
  bool m_available;
};

#endif // COSMOS_SHADER_H
