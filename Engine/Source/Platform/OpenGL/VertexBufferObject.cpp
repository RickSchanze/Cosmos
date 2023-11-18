//
// Created by Echo on 2023/10/3.
//

#include "Platform/OpenGL/VertexBufferObject.h"

#include "Resource/Model.h"
#include "glad/glad.h"

VertexBufferObject::VertexBufferObject(DataLayoutOfVbo data_layout1, DataLayoutOfVbo data_layout2,
                                       DataLayoutOfVbo data_layout3, DataLayoutOfVbo data_layout4) {
  glGenBuffers(1, &m_VBO_id);
  m_data_layout[0] = data_layout1;
  m_data_layout[1] = data_layout2;
  m_data_layout[2] = data_layout3;
  m_data_layout[3] = data_layout4;
}

VertexBufferObject::~VertexBufferObject() {
  Unbind();
  glDeleteBuffers(1, &m_VBO_id);
}

void VertexBufferObject::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_VBO_id); }

void VertexBufferObject::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

void VertexBufferObject::SetData(const void *data, uint32_t size) const {
  Bind();
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
