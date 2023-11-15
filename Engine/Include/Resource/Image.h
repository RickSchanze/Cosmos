/**
 * @file Texture.h
 * @author Echo
 * @Date 2023/11/15
 * @brief
 */

#ifndef TEXTURE_H
#define TEXTURE_H
#include "Global/Typedefs.h"

#include <string>

namespace Resource {

class Image {
public:
  /** 加载位于path的图像文件 */
  static Image *Create(const std::string &path);

public:
  explicit Image(const std::string &path);
  ~Image();

public:
  uint32 *GetData() const { return m_data; }
  int32 GetWidth() const { return m_width; }
  int32 GetHeight() const { return m_height; }
  int32 GetChannel() const { return m_channel; }
  const std::string &GetFilePath() const { return m_path; }
  bool IsValid() const { return m_data != nullptr && m_width >= 0 && m_height >= 0 && m_channel >= 0; }

protected:
  void Create();

private:
  uint32 *m_data = nullptr;
  int32 m_width = 0;
  int32 m_height = 0;
  int32 m_channel = 0;
  std::string m_path;
};

} // namespace Resource

#endif // TEXTURE_H
