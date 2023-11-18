//
// Created by Echo on 2023/10/3.
//

#include "Platform/OpenGL/VertexArrayObject.h"
#include "Platform/OpenGL/VertexBufferObject.h"
#include "Resource/Model.h"
#include "glad/glad.h"

VertexArrayObject::VertexArrayObject() { glGenVertexArrays(1, &m_VAO_id); }

VertexArrayObject::~VertexArrayObject() {
  glBindVertexArray(0);
  glDeleteVertexArrays(1, &m_VAO_id);
}

void VertexArrayObject::Bind() const { glBindVertexArray(m_VAO_id); }

void VertexArrayObject::Unbind() const { glBindVertexArray(0); }

void VertexArrayObject::AttributeVBO(const VertexBufferObject &vbo, int row_size) {
  const auto layouts = vbo.GetDataLayouts();
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

void VertexArrayObject::AttributeVBOVertex(const VertexBufferObject &vbo){
  vbo.Bind();
  // 顶点位置
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<void *>(0));
  // 顶点法线
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, Normal)));
  // 顶点纹理坐标
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, TexCoord)));
}
