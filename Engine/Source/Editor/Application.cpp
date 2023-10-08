//
// Created by Echo on 2023/10/3.
//

#include "Editor/Application.h"
#include "Core/Log/Logger.h"
#include "Editor/EditorUIHelper.h"
#include "Editor/UI/DebugWidget.h"
#include "Editor/UI/SceneViewWidget.h"
#include "Function/Event/GameEvent.h"
#include "Function/Event/KeyEventHelper.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

void Application::MainLoop() {
  BeginPlay();
  while (!glfwWindowShouldClose(m_main_window)) {
    TickLogic();
    TickRender();
    TickEditorUI();
    TickEndFrame();
  }
  EndPlay();
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
}

Application *Application::GetApplication() {
  if (m_application != nullptr) {
    return m_application;
  }
  m_application = new Application();
  return m_application;
}

void Application::TickLogic() { m_main_scene_view_widget->TickLogic(); }

void Application::TickRender() {
  // 主窗口必修绑定帧缓冲不然没办法显示
  ASSERT(m_main_scene_view_widget != nullptr, "pointer to main scene view widget is nullptr");
  m_main_scene_view_widget->BeginRender();
  m_main_scene_view_widget->TickRender();
  m_main_scene_view_widget->EndRender();
}

void Application::TickEditorUI() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
  // 检测键盘事件
  for (int key = ImGuiKey_NamedKey_BEGIN; key < ImGuiKey_COUNT; key++) {
    if (ImGui::IsKeyPressed((ImGuiKey)key, false)) {
      KeyPressedEvent event{GetKeyCode(key)};
      GameEvent::OnKeyPressed.Invoke(event);
    }
    if (ImGui::IsKeyReleased((ImGuiKey)key)) {
      KeyReleasedEvent event{GetKeyCode(key)};
      GameEvent::OnKeyReleased.Invoke(event);
    }
    if (ImGui::IsKeyDown((ImGuiKey)key)) {
      KeyDownEvent event{GetKeyCode(key)};
      GameEvent::OnKeyDown.Invoke(event);
    }
  }
  // OpenGLMainWindow的GUI
  ImGui::Begin("全局信息", nullptr);
  ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
  ImGui::End();

  if (m_main_scene_view_widget != nullptr) {
    m_main_scene_view_widget->Render();
  }

  for (auto &widget : m_widgets) {
    widget->Render();
  }

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Application::TickEndFrame() {
  m_main_scene_view_widget->TickEndFrame();

  if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    GLFWwindow *backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);
  }

  glfwPollEvents();
  glfwSwapBuffers(m_main_window);
}

void Application::OtherShutdown() {
  // 删除主显示对象
  delete m_main_scene_view_widget;
  // 删除其他的Widget
  for (auto &widget : m_widgets) {
    delete widget;
  }
}

void Application::OtherInitialize() {
  m_main_scene_view_widget = new Editor::SceneViewWidget("场景");
  AddWidget<Editor::DebugWidget>("调试");
}

void Application::BeginPlay() { m_main_scene_view_widget->BeginPlay(); }

void Application::EndPlay() { m_main_scene_view_widget->EndPlay(); }

template <typename T>
requires Editor::IsWidget<T>
T *Application::AddWidget(std::string name) {
  // 检查名字是否重复
  if (std::find_if(m_widgets.begin(), m_widgets.end(), [&name](Editor::Widget *w) { return w->GetName() == name; }) !=
      m_widgets.end()) {
    LOG_ERROR("添加Widget失败，名字为{}的widget已存在", name);
    return nullptr;
  }
  T *w = new T();
  w->SetName(name);
  m_widgets.push_back(w);
  return w;
}
