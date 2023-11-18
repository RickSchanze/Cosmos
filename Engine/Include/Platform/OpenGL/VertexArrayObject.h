//
// Created by Echo on 2023/10/3.
//

#ifndef COSMOS_VERTEXARRAYOBJECT_H
#define COSMOS_VERTEXARRAYOBJECT_H

#include "VertexBufferObject.h"

#include <cstdint>


class VertexBufferObject;

/**
 * NOTE:
 * VBO在析构时会删除显存里的缓冲区
 * 而如果此时VAO还持有这个VBO那么就可能出问题
 */

class VertexArrayObject {
public:
  VertexArrayObject();

  ~VertexArrayObject();

  void Bind() const;
  void Unbind() const;

  void AttributeVBO(const VertexBufferObject &vbo, int i);

  void AttributeVBOVertex(const VertexBufferObject &vbo);

private:
  uint32_t m_VAO_id{};
};

#endif // COSMOS_VERTEXARRAYOBJECT_H
