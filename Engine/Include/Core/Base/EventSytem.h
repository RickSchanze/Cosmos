//
// Created by Echo on 2023/10/6.
// 基于枚举的事件机制
//

#ifndef COSMOS_EVENT_H
#define COSMOS_EVENT_H
#include <functional>
#include <map>
#include <string>
#include <utility>

template <typename... Args>
class Delegate {
public:
  void operator()(Args... args) const { m_function(args...); }

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
  void AddEventListener(Delegate<Args...> delegate) { m_event_listeners.push_back(std::move(delegate)); }

  template <typename ObjectType, typename ClassFunc>
  void AddEventListener(std::string name, ObjectType *obj, ClassFunc func) {
    m_event_listeners.emplace_back(std::move(name), obj, func);
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

  template <typename... InvokeArgs>
  void Invoke(InvokeArgs... args) {
    for (auto &listener : m_event_listeners) {
      listener(args...);
    }
  }

  [[nodiscard]] size_t Size() const { return m_event_listeners.size(); }

private:
  // 可能后期可以使用std::map优化?
  std::vector<Delegate<Args...>> m_event_listeners;
};

#endif // COSMOS_EVENT_H
