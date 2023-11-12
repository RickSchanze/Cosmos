/**
 * @file Concepts.h
 * @author Echo
 * @Date 2023/10/7
 * @brief
 */

#ifndef COSMOS_CONCEPTS_H
#define COSMOS_CONCEPTS_H
// 这里必须包含,不然内部编译器错误
#include <utility>

namespace Editor {
class Widget;

template <typename T>
concept IsWidget = std::is_base_of_v<Widget, T>;
} // namespace Editor

#endif // COSMOS_CONCEPTS_H
