//
// Created by Echo on 2023/10/3.
//

#include "Editor/Application.h"
#include "Editor/EditorUIHelper.h"
#include "Function/Logger.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

void Application::MainLoop() {
  while (!glfwWindowShouldClose(m_main_window)) {
    TickLogic();
    TickRender();
    TickEditorUI();
    TickEndFrame();
  }
}

void Application::Run() {
  ImGuiInitialize();
  OtherInitialize();
  MainLoop();
  OtherShutdown();
  ImGuiShutdown();
}

void Application::glfwShutdown() {
  glfwDestroyWindow(m_main_window);
  glfwTerminate();
}

void Application::glfwInitialize() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  m_main_window = glfwCreateWindow(m_width, m_height, "Cosmos", nullptr, nullptr);
  if (m_main_window == nullptr) {
    LOG_ERROR("初始化GLFW失败");
    glfwTerminate();
    return;
  }

  glfwMakeContextCurrent(m_main_window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    LOG_ERROR("初始化GLAD失败");
    glfwTerminate();
    return;
  }
}

void Application::ImGuiShutdown() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void Application::ImGuiInitialize() {
  std::string version = (const char *)glGetString(GL_VERSION);
  LOG_INFO("OpenGL版本: {}", version);
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  auto &io = ImGui::GetIO();
  (void)io;
  io.Fonts->AddFontFromFileTTF("c:/windows/fonts/msyh.ttc", 24.0f, nullptr,
                               io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
  io.FontDefault = io.Fonts->Fonts[0];
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
                                                        //    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; //
                                                        //    Enable Gamepad Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows
  ImGui::StyleColorsDark();
  EditorUIHelper::SetStyleDark(ImGui::GetStyle());
  ImGui_ImplGlfw_InitForOpenGL(m_main_window, true);
  ImGui_ImplOpenGL3_Init("#version 460");
}

Application::Application() { glfwInitialize(); }

Application::~Application() {
  glfwShutdown();
  delete m_application;
  delete m_frame_buffer_object;
}

Application *Application::GetApplication() {
  if (m_application != nullptr) {
    return m_application;
  }
  m_application = new Application();
  return m_application;
}

void Application::TickLogic() {}

void Application::TickRender() {
  m_frame_buffer_object->Bind();
  glClearColor(1.f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  m_frame_buffer_object->Unbind();
}

void Application::TickEditorUI() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
  // OpenGLMainWindow的GUI
  ImGui::Begin("全局信息", nullptr);
  ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
  ImGui::End();
  ImGui::Begin("场景");
  ImGui::Image(reinterpret_cast<ImTextureID>(m_frame_buffer_object->GetFBO()), ImGui::GetContentRegionAvail(),
               ImVec2(0, 1), ImVec2(1, 0));
  ImGui::End();

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Application::TickEndFrame() {
  if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    GLFWwindow *backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);
  }

  glfwPollEvents();
  glfwSwapBuffers(m_main_window);
}

void Application::OtherShutdown() { delete m_frame_buffer_object; }

void Application::OtherInitialize() { m_frame_buffer_object = new FrameBufferObject(); }
