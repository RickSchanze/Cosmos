/**
 * @file EventSystem.h
 * @author
 * @brief 事件系统
 * 注意：
 * 1.如果将对象的成员函数以及对象传递给Event
 * 那么一定要在对象析构时取消注册Event
 * 否则很可能崩溃
 * 2.如果增加时拥有同名的Delegate，那么会被覆盖
 */

#ifndef COSMOS_EVENT_H
#define COSMOS_EVENT_H
#include <functional>
#include <map>
#include <set>
#include <string>
#include <utility>

template <typename... Args>
class Delegate {
public:
  // 这里使用了模版和完美转发
  template <class... InvokeArgs>
  void operator()(InvokeArgs &&...args) const {
    m_function(std::forward<InvokeArgs...>(args...));
  }

  auto operator<=>(const Delegate<Args...> &rhs) const { return m_name <=> rhs.m_name; }

  template <typename ObjectType, typename ClassFuncType>
  explicit Delegate(std::string name, ObjectType *obj, ClassFuncType func) : m_name(std::move(name)) {
    Swap(obj, func);
  }

  template <typename Func>
  explicit Delegate(std::string name, Func func) : m_name(std::move(name)) {
    Swap(func);
  }

  template <typename ObjectType, typename ClassFuncType>
  void Swap(ObjectType *obj, ClassFuncType func) {
    auto func_ = [obj, func](Args... args) { (obj->*func)(args...); };
    m_function = std::move(func_);
  }

  template <typename Func>
  void Swap(Func func) {
    m_function = std::move(func);
  }

  explicit Delegate(std::string name, std::function<void(Args...)> func) : m_name(std::move(name)) {
    m_function = std::move(func);
  }

  [[nodiscard]] inline const std::string &GetName() const { return m_name; }
  inline void SetName(std::string name) { m_name = std::move(name); }

private:
  std::function<void(Args...)> m_function;
  std::string m_name;
};

template <typename... Args>
class Event {
public:
  Event() = default;
  // 禁止拷贝构造和赋值
  Event(const Event<Args...> &) = delete;
  Event &operator=(const Event<Args...> &) = delete;

  /*
   * @brief 添加事件监听器,使用了std::move因此如果调用了此函数就不要使用delegate来调用函数了
   */
  void AddEventListener(Delegate<Args...> delegate) { m_event_listeners.push_back(std::move(delegate)); }

  template <typename ObjectType, typename ClassFunc>
  void AddEventListener(std::string name, ObjectType *obj, ClassFunc func) {
    m_event_listeners.emplace_back(name, obj, func);
  }

  template <typename Func>
  void AddEventListener(std::string name, Func func) {
    m_event_listeners.emplace_back(std::move(name), func);
  }

  void RemoveEventListener(std::string name) {
    auto it = std::find_if(m_event_listeners.begin(), m_event_listeners.end(),
                           [&name](const Delegate<Args...> &delegate) { return delegate.GetName() == name; });
    if (it != m_event_listeners.end()) {
      m_event_listeners.erase(it);
    }
  }

  // 使用模版和完美转发
  template <typename... InvokeArgs>
  void Invoke(InvokeArgs &&...args) {
    for (auto &listener : m_event_listeners) {
      listener(std::forward<InvokeArgs...>(args...));
    }
  }

  [[nodiscard]] size_t Size() const { return m_event_listeners.size(); }

private:
  std::vector<Delegate<Args...>> m_event_listeners;
};

#endif // COSMOS_EVENT_H
