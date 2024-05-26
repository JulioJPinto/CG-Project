#include "input.hpp"
#include "fmt/core.h"
#include "menuimgui.hpp"

#include <cassert>
#include <cstdint>
#include <unordered_map>

#include <GL/freeglut_std.h>


void Input::on_key_down(unsigned char native_key, int x, int y) {
    s_keyboard_state[native_to_key(native_key)] = true;
    ImGui_ImplGLUT_KeyboardFunc(native_key, x, y);
}

void Input::on_key_up(unsigned char native_key, int x, int y) {
    s_keyboard_state[native_to_key(native_key)] = false;
    ImGui_ImplGLUT_KeyboardUpFunc(native_key, x, y);
}

void Input::on_special_key_down(int native_key, int x, int y) {
    s_keyboard_state[special_native_to_key(native_key)] = true;
    ImGui_ImplGLUT_SpecialFunc(native_key, x, y);
}

void Input::on_special_key_up(int native_key, int x, int y) {
    s_keyboard_state[special_native_to_key(native_key)] = false;
    ImGui_ImplGLUT_SpecialUpFunc(native_key, x, y);
}

void Input::on_mouse_motion(int x, int y) {
    s_mouse_position = glm::ivec2{x, y};
    ImGui_ImplGLUT_MotionFunc(x, y);
}

void Input::on_mouse_button(int native_button, int state, int x, int y) {
    s_mouse_state[native_to_button(native_button)] = GLUT_DOWN == state;
    ImGui_ImplGLUT_MouseFunc(native_button, state, x, y);
}

void Input::process_input() {
    static glm::ivec2 prev_position = s_mouse_position;
    s_mouse_delta = s_mouse_position - prev_position;
    prev_position = s_mouse_position;
}

bool Input::is_down(Keyboard::Key key) {
    assert(key < s_keyboard_state.size());
    return s_keyboard_state.test(key);
}

bool Input::is_up(Keyboard::Key key) {
    assert(key < s_keyboard_state.size());
    return !s_keyboard_state.test(key);
}

bool Input::is_down(Mouse::Button button) {
    assert(button < s_mouse_state.size());
    return s_mouse_state.test(button);
}

bool Input::is_up(Mouse::Button button) {
    assert(button < s_mouse_state.size());
    return !s_mouse_state.test(button);
}

Keyboard::Key Input::native_to_key(unsigned char key_code) {
    if (key_code >= 'A' && key_code <= 'Z') {
        return Keyboard::Key(key_code - 'A');
    }
    else if (key_code >= 'a' && key_code <= 'z') {
        return Keyboard::Key(key_code - 'a');
    }

    return Keyboard::UnknownKey;
}

Keyboard::Key Input::special_native_to_key(int key_code) {
    static std::unordered_map<int, Keyboard::Key> special_key_mapping{
        {GLUT_KEY_F1, Keyboard::F1},
        {GLUT_KEY_F2, Keyboard::F2},
        {GLUT_KEY_F3, Keyboard::F3},
        {GLUT_KEY_F4, Keyboard::F4},
        {GLUT_KEY_F5, Keyboard::F5},
        {GLUT_KEY_F6, Keyboard::F6},
        {GLUT_KEY_F7, Keyboard::F7},
        {GLUT_KEY_F8, Keyboard::F8},
        {GLUT_KEY_F9, Keyboard::F9},
        {GLUT_KEY_F10, Keyboard::F10},
        {GLUT_KEY_F11, Keyboard::F11},
        {GLUT_KEY_F12, Keyboard::F12},
        {GLUT_KEY_LEFT, Keyboard::Left},
        {GLUT_KEY_UP, Keyboard::Up},
        {GLUT_KEY_RIGHT, Keyboard::Right},
        {GLUT_KEY_DOWN, Keyboard::Down},
        {GLUT_KEY_PAGE_UP, Keyboard::PageUp},
        {GLUT_KEY_PAGE_DOWN, Keyboard::PageDown},
        {GLUT_KEY_HOME, Keyboard::Home},
        {GLUT_KEY_END, Keyboard::End},
        {GLUT_KEY_INSERT, Keyboard::Insert},
        // GLUT undocumented special keys
        {112, Keyboard::LShift},
        {113, Keyboard::RShift},
        {114, Keyboard::LCtrl},
        {115, Keyboard::RCtrl},
        {115, Keyboard::Alt},
        {118, Keyboard::Mod},
    };

    const auto it = special_key_mapping.find(key_code);
    return (it != special_key_mapping.end()) ? it->second
                                             : Keyboard::UnknownKey;
}

Mouse::Button Input::native_to_button(int button_code) {
    // Shouldn't be possible to emmit another button_code value.
    if (button_code >= 0 && button_code < 3) {
        return Mouse::Button(button_code);
    }

    return Mouse::UnknownButton;
}
