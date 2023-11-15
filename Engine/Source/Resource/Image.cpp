/**
 * @file Texture.cpp
 * @author Echo 
 * @Date 2023/11/15
 * @brief 
 */

#define STB_IMAGE_IMPLEMENTATION

#include "Resource/Image.h"

#include "Core/Log/Logger.h"

#include <stb_image.h>

namespace Resource {
Image *Image::Create(const std::string &path) {
  return new Image(path);
}

Image::Image(const std::string &path) {
  m_path = path;
  Create();
}

Image::~Image() { stbi_image_free(m_data); }

void Image::Create() {
  stbi_uc* pixels = stbi_load(m_path.c_str(), &m_width, &m_height, &m_channel, 0);
  if (!pixels) {
    LOG_ERROR("图像加载失败:{}", m_path);
    return;
  }
  m_data = reinterpret_cast<uint32*>(pixels);
}
} // Resource
