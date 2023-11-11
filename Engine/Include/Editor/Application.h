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
  struct MousePosition {
    MousePosition() {
      LastX = 0.f;
      LastY = 0.f;
      XOffset = 0.f;
      YOffset = 0.f;
      FirstMouse = true;
    }
    float LastX;
    float LastY;
    float XOffset;
    float YOffset;
    bool FirstMouse;
  };

  ~Application();

  void Run();
  void MainLoop();
  void BeginPlay();
  void EndPlay();
  static Application *GetApplication();

  inline Editor::SceneViewWidget* GetMainSceneViewWidget() { return m_main_scene_view_widget; }

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

  void LockMouse_GLFW(bool lock);
  std::string GetLockMouseEventHandlerName();

  template <typename T>
  requires Editor::IsWidget<T>
  T *AddWidget(std::string name);

  static void MouseMoveCallback_GLFW(GLFWwindow *window, double xpos, double ypos);

private:
  GLFWwindow *m_main_window = nullptr;
  static inline Application *m_application = nullptr;

  int m_width{1920};
  int m_height{1080};
  Editor::SceneViewWidget *m_main_scene_view_widget = nullptr;
  std::vector<Editor::Widget *> m_widgets;

  // 处理鼠标移动事件
  static inline MousePosition m_mouse_position;
};

#endif // COSMOS_APPLICATION_H
