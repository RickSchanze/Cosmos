/**
 * @file OpenGLTexture.h
 * @author Echo 
 * @Date 2023/11/15
 * @brief 
 */

#ifndef OPENGLTEXTURE_H
#define OPENGLTEXTURE_H
#include "Global/Typedefs.h"

namespace Resource {
class Image;
}
class Texture {
public:
  /**
   * \brief
   * \param image 图像资源
   * \param index 标识当前纹理使用哪个索引,默认为0
   */
  explicit Texture(const Resource::Image *image, int index = 0);
  ~Texture();
  void Bind();
  void Bind(int32 Index);

private:
  uint32 m_texture_index = 0;
  uint32 m_id;
};



#endif //OPENGLTEXTURE_H
