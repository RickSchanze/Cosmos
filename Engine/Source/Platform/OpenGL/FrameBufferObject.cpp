//
// Created by Echo on 2023/10/3.
//

#include "Platform/OpenGL/FrameBufferObject.h"
#include "Function/Logger.h"
#include "glad/glad.h"
FrameBufferObject::FrameBufferObject() {
  // 帧缓冲配置
  glGenFramebuffers(1, &m_FBO_id);
  glBindFramebuffer(GL_FRAMEBUFFER, m_FBO_id);
  glGenTextures(1, &m_frame_texture_id);
  glBindTexture(GL_TEXTURE_2D, m_frame_texture_id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1280, 720, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // GL_NEAREST
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // GL_NEAREST
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_frame_texture_id, 0);
  // 渲染缓冲配置
  glGenRenderbuffers(1, &m_RBO_id);
  glBindRenderbuffer(GL_RENDERBUFFER, m_RBO_id);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1280, 720);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO_id);
  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    LOG_ERROR("帧缓冲不完整");
    exit(1);
  }
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBufferObject::~FrameBufferObject() {
  glDeleteFramebuffers(1, &m_FBO_id);
  glDeleteRenderbuffers(1, &m_RBO_id);
  glDeleteTextures(1, &m_frame_texture_id);
}

void FrameBufferObject::Bind() const { glBindFramebuffer(GL_FRAMEBUFFER, m_FBO_id); }

void FrameBufferObject::Unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

void FrameBufferObject::Resize(int x, int y) const {
  ResizeFrameBuffer(x, y);
  ResizeRenderBuffer(x, y);
}

void FrameBufferObject::ResizeFrameBuffer(int x, int y) const {
  glBindTexture(GL_TEXTURE_2D, m_frame_texture_id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void FrameBufferObject::ResizeRenderBuffer(int x, int y) const {
  glBindRenderbuffer(GL_RENDERBUFFER, m_RBO_id);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, x, y);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
}
