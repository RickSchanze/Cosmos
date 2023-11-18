/**
 * @file OpenGLTexture.cpp
 * @author Echo
 * @Date 2023/11/15
 * @brief
 */

#include "Platform/OpenGL/Texture.h"

#include "Core/Log/Logger.h"
#include "Resource/Image.h"
#include "glad/glad.h"


Texture::Texture(const Resource::Image *image, const TextureType type) {
  if (image && image->IsValid()) {
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);
    // 纹理环绕参数
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // GL_CLAMP_TO_EDGE
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // GL_CLAMP_TO_EDGE
    // 纹理过滤参数
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // GL_NEAREST
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // GL_NEAREST
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->GetWidth(), image->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image->GetData());
    glGenerateMipmap(GL_TEXTURE_2D);
    m_type = type;
    m_path = image->GetFilePath();
  } else {
    LOG_ERROR("纹理创建失败,图像无效,路径:{}", image->GetFilePath());
  }
}
Texture::~Texture(){
}

void Texture::Activate(const int32 Index) { glActiveTexture(GL_TEXTURE0 + Index); }

void Texture::Bind() { glBindTexture(GL_TEXTURE_2D, m_id); }

std::string Texture::GetTextureTypeString() const {
  switch (m_type) {
  case TextureType::Diffuse:
    return "texture_diffuse";
  case TextureType::Specular:
    return "texture_specular";
  case TextureType::Normal:
    return "texture_normal";
  case TextureType::Height:
    return "texture_height";
  case TextureType::Custom:
    return "texture_custom";
  default:
    return "texture_unknown";
  }
}
