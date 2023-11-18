//
// Created by Echo on 2023/10/3.
//

#include "Platform/OpenGL/ElementBufferObject.h"

#include <glad/glad.h>
ElementBufferObject::ElementBufferObject() { glGenBuffers(1, &m_id); }

ElementBufferObject::~ElementBufferObject() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &m_id);
}

void ElementBufferObject::Bind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void ElementBufferObject::Unbind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ElementBufferObject::BindData(const uint32 *data, const uint32 size) {
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
