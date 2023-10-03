//
// Created by Echo on 2023/10/3.
//

#ifndef COSMOS_APPLICATION_H
#define COSMOS_APPLICATION_H
#include "glad/glad.h"

#include "GLFW/glfw3.h"
#include "Platform/OpenGL/FrameBufferObject.h"

class Application {
public:
  ~Application();

  void Run();
  void MainLoop();
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

private:
  GLFWwindow *m_main_window = nullptr;
  static inline Application *m_application = nullptr;

  int m_width{1920};
  int m_height{1080};
  FrameBufferObject *m_frame_buffer_object;
};

#endif // COSMOS_APPLICATION_H
