//
// Created by Echo on 2023/10/3.
//

#include "Platform/OpenGL/VertexArrayObject.h"
#include "Platform/OpenGL/VertexBufferObject.h"
#include "glad/glad.h"

VertexArrayObject::VertexArrayObject() { glGenVertexArrays(1, &m_VAO_id); }

VertexArrayObject::~VertexArrayObject() {
  glBindVertexArray(0);
  glDeleteVertexArrays(1, &m_VAO_id);
}

void VertexArrayObject::Bind() const { glBindVertexArray(m_VAO_id); }

void VertexArrayObject::Unbind() const { glBindVertexArray(0); }

void VertexArrayObject::AttributeVBO(const VertexBufferObject &vbo, int row_size) {
  auto layouts = vbo.GetDataLayouts();
  int offset = 0;
  vbo.Bind();
  for (int i = 0; i < 4; i++) {
    if (layouts[i] == DataLayoutOfVbo::None) {
      return;
    }
    glEnableVertexAttribArray(i);
    switch (layouts[i]) {
    case DataLayoutOfVbo::Position:
      glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, row_size, reinterpret_cast<void *>(offset));
      offset += 3 * sizeof(float);
      break;
    case DataLayoutOfVbo::Color:
      glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, row_size, reinterpret_cast<void *>(offset));
      offset += 3 * sizeof(float);
      break;
    case DataLayoutOfVbo::ColorAlpha:
      glVertexAttribPointer(i, 4, GL_FLOAT, GL_FALSE, row_size, reinterpret_cast<void *>(offset));
      offset += 4 * sizeof(float);
      break;
    case DataLayoutOfVbo::Normal:
      glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, row_size, reinterpret_cast<void *>(offset));
      offset += 3 * sizeof(float);
      break;
    case DataLayoutOfVbo::TexCoord:
      glVertexAttribPointer(i, 2, GL_FLOAT, GL_FALSE, row_size, reinterpret_cast<void *>(offset));
      offset += 2 * sizeof(float);
      break;
    case DataLayoutOfVbo::None:
      break;
    default:
      break;
    }
  }
}
