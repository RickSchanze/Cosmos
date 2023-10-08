/**
 * @file Shader.cpp
 * @author Echo
 * @Date 2023/10/8
 * @brief
 */
#include <filesystem>
#include <fstream>
#include <sstream>

#include "Core/Log/Logger.h"
#include "Platform/OpenGL/Shader.h"
#include "glad/glad.h"

namespace fs = std::filesystem;

Shader::Shader(const char *vert_shader_path, const char *frag_shader_path)
    : m_available(false), m_frag_shader_code(nullptr), m_vert_shader_code(nullptr) {
  fs::path vert_file{vert_shader_path};
  if (!fs::exists(vert_file)) {
    LOG_ERROR("Vertex shader file not found: {}", vert_shader_path);
    return;
  }
  fs::path frag_file{frag_shader_path};
  if (!fs::exists(frag_file)) {
    LOG_ERROR("Fragment shader file not found: {}", frag_shader_path);
    return;
  }

  std::ifstream vert_file_in{vert_file};
  if (!vert_file_in.is_open()) {
    LOG_ERROR("Failed to read vertex shader file: {}", vert_shader_path);
    return;
  }
  std::ifstream frag_file_in{frag_file};
  if (!frag_file_in.is_open()) {
    LOG_ERROR("Failed to read fragment shader file: {}", frag_shader_path);
    return;
  }
  std::stringstream vert_stream;
  vert_stream << vert_file_in.rdbuf();
  vert_file_in.close();
  auto vert_str = vert_stream.str();
  m_vert_shader_code = vert_str.c_str();

  std::stringstream frag_stream;
  frag_stream << frag_file_in.rdbuf();
  frag_file_in.close();
  auto frag_str = frag_stream.str();
  m_frag_shader_code = frag_str.c_str();

  // 生成shader程序
  uint32_t vert, frag;
  int success;
  char infoLog[512];

  vert = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vert, 1, &m_vert_shader_code, nullptr);
  glCompileShader(vert);
  glGetShaderiv(vert, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vert, 512, nullptr, infoLog);
    LOG_ERROR("Vertex shader compile failed: {}", infoLog);
    return;
  }

  frag = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag, 1, &m_frag_shader_code, nullptr);
  glCompileShader(frag);
  glGetShaderiv(frag, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(frag, 512, nullptr, infoLog);
    LOG_ERROR("Fragment shader complied failed: {}", infoLog);
    return;
  }

  m_id = glCreateProgram();
  glAttachShader(m_id, vert);
  glAttachShader(m_id, frag);
  glLinkProgram(m_id);
  glGetProgramiv(m_id, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(m_id, 512, nullptr, infoLog);
    LOG_ERROR("Shader program {} link failed: {}", m_id, infoLog);
    return;
  }

  glDeleteShader(vert);
  glDeleteShader(frag);
  m_available = true;
  LOG_INFO("Shader program {} successes!", m_id);
}

void Shader::Use() {
  if (!m_available) {
    LOG_ERROR("Shader program {} is not available!", m_id);
    return;
  }
  glUseProgram(m_id);
}

void Shader::SetBool(const std::string &name, bool value) const {
  if (!m_available) {
    LOG_ERROR("Shader program {} is not available!", m_id);
    return;
  }
  glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string &name, int value) const {
  if (!m_available) {
    LOG_ERROR("Shader program {} is not available!", m_id);
    return;
  }
  glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::SetUInt(const std::string &name, unsigned int value) const {
  if (!m_available) {
    LOG_ERROR("Shader program {} is not available!", m_id);
    return;
  }
  glUniform1ui(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::SetFloat(const std::string &name, float value) const {
  if (!m_available) {
    LOG_ERROR("Shader program {} is not available!", m_id);
    return;
  }
  glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::SetMatrix4f(const std::string &name, const glm::mat4 &value) const {
  if (!m_available) {
    LOG_ERROR("Shader program {} is not available!", m_id);
    return;
  }
  glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::SetVec3(const std::string &name, const glm::vec3 &value) const {
  if (!m_available) {
    LOG_ERROR("Shader program {} is not available!", m_id);
    return;
  }
  glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
}
