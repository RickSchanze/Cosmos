#include "Editor/Application.h"
#include "Windows.h"

int main() {
  SetConsoleOutputCP(CP_UTF8);
  Application *app = Application::GetApplication();
  app->Run();
  return 0;
}
