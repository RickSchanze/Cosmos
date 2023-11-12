/**
 * !important
 * VBO是资源，请务必使用智能指针管理
 */

#ifndef COSMOS_VERTEXBUFFEROBJECT_H
#define COSMOS_VERTEXBUFFEROBJECT_H
#include <cstdint>

enum class DataLayoutOfVbo {
  Position,   // 顶点位置属性
  Color,      // 顶点颜色属性
  ColorAlpha, // 带Alpha的颜色
  Normal,     // 顶点法线属性
  TexCoord,   // 顶点纹理坐标属性
  None        // 表示没了
};

class VertexBufferObject {
public:
  /**
   * @brief 构造函数，四个layout表示如何解释VBO数据，按顺序解释
   * @param data_layout1
   * @param data_layout2
   * @param data_layout3
   * @param data_layout4
   */
  explicit VertexBufferObject(DataLayoutOfVbo data_layout1, DataLayoutOfVbo data_layout2 = DataLayoutOfVbo::None,
                              DataLayoutOfVbo data_layout3 = DataLayoutOfVbo::None, DataLayoutOfVbo data_layout4 = DataLayoutOfVbo::None);
  ~VertexBufferObject();

  void Bind() const;
  void Unbind() const;

  void SetData(const void *data, uint32_t size) const;

  uint32_t GetVBO() const { return m_VBO_id; }
  const DataLayoutOfVbo *const GetDataLayouts() const { return m_data_layout; }

private:
  uint32_t m_VBO_id{};
  DataLayoutOfVbo m_data_layout[4] = {DataLayoutOfVbo::None};
};

#endif // COSMOS_VERTEXBUFFEROBJECT_H
