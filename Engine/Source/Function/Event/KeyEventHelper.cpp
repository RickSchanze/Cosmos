/**
 * @file KeyEventHelper.cpp
 * @author Echo
 * @Date 2023/10/7
 * @brief
 */

#include "Function/Event/KeyEventHelper.h"
#include "imgui.h"

KeyCode GetKeyCode(int key) {
  KeyCode code = KeyCode::Unknown;
  switch (key) {
  case ImGuiKey_A:
    code = KeyCode::A;
    break;
  case ImGuiKey_B:
    code = KeyCode::B;
    break;
  case ImGuiKey_C:
    code = KeyCode::C;
    break;
  case ImGuiKey_D:
    code = KeyCode::D;
    break;
  case ImGuiKey_E:
    code = KeyCode::E;
    break;
  case ImGuiKey_F:
    code = KeyCode::F;
    break;
  case ImGuiKey_G:
    code = KeyCode::G;
    break;
  case ImGuiKey_H:
    code = KeyCode::H;
    break;
  case ImGuiKey_I:
    code = KeyCode::I;
    break;
  case ImGuiKey_J:
    code = KeyCode::J;
    break;
  case ImGuiKey_K:
    code = KeyCode::K;
    break;
  case ImGuiKey_L:
    code = KeyCode::L;
    break;
  case ImGuiKey_M:
    code = KeyCode::M;
    break;
  case ImGuiKey_N:
    code = KeyCode::N;
    break;
  case ImGuiKey_O:
    code = KeyCode::O;
    break;
  case ImGuiKey_P:
    code = KeyCode::P;
    break;
  case ImGuiKey_Q:
    code = KeyCode::Q;
    break;
  case ImGuiKey_R:
    code = KeyCode::R;
    break;
  case ImGuiKey_S:
    code = KeyCode::S;
    break;
  case ImGuiKey_T:
    code = KeyCode::T;
    break;
  case ImGuiKey_U:
    code = KeyCode::U;
    break;
  case ImGuiKey_V:
    code = KeyCode::V;
    break;
  case ImGuiKey_W:
    code = KeyCode::W;
    break;
  case ImGuiKey_X:
    code = KeyCode::X;
    break;
  case ImGuiKey_Y:
    code = KeyCode::Y;
    break;
  case ImGuiKey_Z:
    code = KeyCode::Z;
    break;
  case ImGuiKey_Escape:
    code = KeyCode::Escape;
    break;
  case ImGuiKey_Space:
    code = KeyCode::Space;
    break;
  }
  return code;
}

std::string GetKeyString(KeyCode code) {
  std::string str = "Unknown";
  switch (code) {
  case KeyCode::A:
    str = "A";
    break;
  case KeyCode::B:
    str = "B";
    break;
  case KeyCode::C:
    str = "C";
    break;
  case KeyCode::D:
    str = "D";
    break;
  case KeyCode::E:
    str = "E";
    break;
  case KeyCode::F:
    str = "F";
    break;
  case KeyCode::G:
    str = "G";
    break;
  case KeyCode::H:
    str = "H";
    break;
  case KeyCode::I:
    str = "I";
    break;
  case KeyCode::J:
    str = "J";
    break;
  case KeyCode::K:
    str = "K";
    break;
  case KeyCode::L:
    str = "L";
    break;
  case KeyCode::M:
    str = "M";
    break;
  case KeyCode::N:
    str = "N";
    break;
  case KeyCode::O:
    str = "O";
    break;
  case KeyCode::P:
    str = "P";
    break;
  case KeyCode::Q:
    str = "Q";
    break;
  case KeyCode::R:
    str = "R";
    break;
  case KeyCode::S:
    str = "S";
    break;
  case KeyCode::T:
    str = "T";
    break;
  case KeyCode::U:
    str = "U";
    break;
  case KeyCode::V:
    str = "V";
    break;
  case KeyCode::W:
    str = "W";
    break;
  case KeyCode::X:
    str = "X";
    break;
  case KeyCode::Y:
    str = "Y";
    break;
  case KeyCode::Z:
    str = "Z";
    break;
  case KeyCode::Escape:
    str = "Escape";
    break;
  case KeyCode::Space:
    str = "Space";
    break;
  case KeyCode::Unknown:
    str = "Unknown";
    break;
  }
  return str;
}
