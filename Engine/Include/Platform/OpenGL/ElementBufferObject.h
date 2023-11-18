//
// Created by Echo on 2023/10/3.
//

#ifndef COSMOS_ELEMENTBUFFEROBJECT_H
#define COSMOS_ELEMENTBUFFEROBJECT_H

#include "Global/Typedefs.h"
class ElementBufferObject {
public:
  ElementBufferObject();
  ~ElementBufferObject();
  void Bind();
  void Unbind();
  void BindData(const uint32 *data, uint32 size);

private:
  uint32 m_id;
};

#endif // COSMOS_ELEMENTBUFFEROBJECT_H
