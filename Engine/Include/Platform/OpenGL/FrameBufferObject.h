//
// Created by Echo on 2023/10/3.
//

#ifndef COSMOS_FRAMEBUFFEROBJECT_H
#define COSMOS_FRAMEBUFFEROBJECT_H
#include <cstdint>

class FrameBufferObject {
public:
  FrameBufferObject();
  ~FrameBufferObject();

  FrameBufferObject(int x, int y);

  void Bind() const;
  void Unbind();
  /**
   * @brief 重新设置缓冲大小，包括帧缓冲和渲染缓冲
   * @param x
   * @param y
   */
  void Resize(int x, int y) const;

  /**
   * @brief 重新设置帧缓冲大小
   */
  void ResizeFrameBuffer(int x, int y) const;

  /**
   * @brief 重新设置渲染缓冲大小
   * @param x
   * @param y
   */
  void ResizeRenderBuffer(int x, int y) const;

  uint32_t GetFBO() const { return m_FBO_id; }
  uint32_t GetRBO() const { return m_RBO_id; }

private:
  uint32_t m_FBO_id{};
  uint32_t m_RBO_id{};
  uint32_t m_frame_texture_id{};
};

#endif // COSMOS_FRAMEBUFFEROBJECT_H
