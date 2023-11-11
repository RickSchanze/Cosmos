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
#include "Global/GlobalDefiniation.h"
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
  glfwSetCursorPosCallback(m_main_window, &Application::MouseMoveCallback_GLFW);
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
  io.Fonts->AddFontFromFileTTF("c:/windows/fonts/msyh.ttc", 24.0f, nullptr, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
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
      KeyPressedEventParams event{KeyEventHelper::GetKeyCode(key)};
      GameEvent::KeyPressedEvent.Dispatch(event);
    }
    if (ImGui::IsKeyReleased((ImGuiKey)key)) {
      KeyReleasedEventParams event{KeyEventHelper::GetKeyCode(key)};
      GameEvent::KeyReleasedEvent.Dispatch(event);
    }
    if (ImGui::IsKeyDown((ImGuiKey)key)) {
      KeyDownEventParams event{KeyEventHelper::GetKeyCode(key)};
      GameEvent::KeyDownEvent.Dispatch(event);
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

void Application::BeginPlay() {
  m_main_scene_view_widget->BeginPlay();
  GameEvent::MouseLockEvent.AddEventListener(GetLockMouseEventHandlerName(), this, &Application::LockMouse_GLFW);
}

void Application::EndPlay() {
  m_main_scene_view_widget->EndPlay();
  GameEvent::MouseLockEvent.RemoveEventListener(GetLockMouseEventHandlerName());
}

void Application::LockMouse_GLFW(bool lock) {
  if (lock) {
    glfwSetInputMode(m_main_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  } else {
    glfwSetInputMode(m_main_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    m_mouse_position.FirstMouse = true;
    // NOTE: 当按ESC解除鼠标锁定时,glfw开始绘制鼠标
    // 但是ImGui实际上还是Focus在场景窗口上
    // 这就会导致鼠标不会再被锁定
    // 因此暂时用这个trick来解决
    // 此窗口必须是存在的窗口,否则不起作用
    ImGui::SetWindowFocus("调试");
  }
}
std::string Application::GetLockMouseEventHandlerName() {
  static const std::string event_name = "Application_MouseLock";
  return event_name;
}

// 检测鼠标是否移动
void Application::MouseMoveCallback_GLFW(GLFWwindow *window, double xpos, double ypos) {
  if (m_mouse_position.FirstMouse) {
    m_mouse_position.LastX = xpos;
    m_mouse_position.LastY = ypos;
    m_mouse_position.FirstMouse = false;
  }

  m_mouse_position.XOffset = xpos - m_mouse_position.LastX;
  m_mouse_position.YOffset = m_mouse_position.LastY - ypos;
  m_mouse_position.LastX = xpos;
  m_mouse_position.LastY = ypos;
  if (m_mouse_position.XOffset != 0 || m_mouse_position.YOffset != 0) {
    MouseMoveEventParams event{m_mouse_position.XOffset, -m_mouse_position.YOffset};
    GameEvent::MouseMoveEvent.Dispatch(event);
  }
}

template <typename T>
requires Editor::IsWidget<T>
T *Application::AddWidget(std::string name) {
  // 检查名字是否重复
  if (std::find_if(m_widgets.begin(), m_widgets.end(), [&name](Editor::Widget *w) { return w->GetName() == name; }) != m_widgets.end()) {
    LOG_ERROR("添加Widget失败，名字为{}的widget已存在", name);
    return nullptr;
  }
  T *w = new T();
  w->SetName(name);
  m_widgets.push_back(w);
  return w;
}
