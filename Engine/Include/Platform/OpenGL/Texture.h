/**
 * @file OpenGLTexture.h
 * @author Echo 
 * @Date 2023/11/15
 * @brief 
 */

#ifndef OPENGLTEXTURE_H
#define OPENGLTEXTURE_H
#include "Global/Typedefs.h"

#include <string>

enum class TextureType {
  Diffuse,
  Specular,
  Normal,
  Height,
  Custom
};

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
  explicit Texture(const Resource::Image *image, TextureType type);
  Texture(const Texture&) = default;
  ~Texture();
  void Activate();
  void Activate(int32 Index);
  void Bind();
  /** 纹理类型 */
  TextureType GetType() const { return m_type; }
  /** OpenGL给出的TextureId */
  uint32 GetId() const { return m_id; }
  /** 激活当前纹理 */

  std::string GetTextureTypeString() const;
  std::string GetFilePath() const { return m_path; }
private:
  uint32 m_id;
  TextureType m_type;
  std::string m_path;
};



#endif //OPENGLTEXTURE_H
