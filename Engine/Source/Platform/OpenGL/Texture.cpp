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

// TODO: 图像加载不应该在构造函数直接写死各个参数
Texture::Texture(const Resource::Image *image, const int index) {
  if (image && image->IsValid()) {
    m_texture_index = index;
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
  } else {
    LOG_ERROR("纹理创建失败,图像无效,路径:{}", image->GetFilePath());
  }
}

Texture::~Texture(){
  glDeleteTextures(1, &m_id);
}

void Texture::Bind() {
  Bind(m_texture_index);
}

void Texture::Bind(const int32 Index){
  glActiveTexture(GL_TEXTURE0 + Index);
  glBindTexture(GL_TEXTURE_2D, m_id);
}
