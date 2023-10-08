//
// Created by Echo on 2023/10/3.
//

#ifndef COSMOS_APPLICATION_H
#define COSMOS_APPLICATION_H
#include "glad/glad.h"

#include "Editor/Concepts.h"
#include "GLFW/glfw3.h"
#include "Platform/OpenGL/FrameBufferObject.h"

#include <string>
#include <vector>

namespace Editor {
class SceneViewWidget;
class Widget;
} // namespace Editor

class Application {
public:
  ~Application();

  void Run();
  void MainLoop();
  void BeginPlay();
  void EndPlay();
  static Application *GetApplication();

private:
  Application();

  void ImGuiInitialize();

  void ImGuiShutdown();

  void glfwInitialize();

  void glfwShutdown();

  void OtherInitialize();

  void OtherShutdown();

  void TickRender();

  void TickEditorUI();

  void TickLogic();

  void TickEndFrame();

  template <typename T>
  requires Editor::IsWidget<T>
  T *AddWidget(std::string name);

private:
  GLFWwindow *m_main_window = nullptr;
  static inline Application *m_application = nullptr;

  int m_width{1920};
  int m_height{1080};
  Editor::SceneViewWidget *m_main_scene_view_widget = nullptr;
  std::vector<Editor::Widget *> m_widgets;
};

#endif // COSMOS_APPLICATION_H
