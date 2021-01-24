#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <algorithm>

#include "Display.h"
#include "Log.h"

static const int NUM_KEYS = 350; // Amount of keys that glfw can handle
static const int NUM_MOUSE_BUTTONS = 9; // Amount of mouse buttons that glfw can handle

class GameContext;

class DesktopInput {

    friend class Input;
    friend class GameContext;

    static std::vector<DesktopInput*> s_Instances;

    // TODO: Optimize by setting the bool to something like 3 if it was pressed last!
    // Will cut the amount of allocated bytes in half!!!!
    bool m_Keys[NUM_KEYS] = { false };
    bool m_KeysLast[NUM_KEYS] = { false };

    bool m_MouseButtons[NUM_MOUSE_BUTTONS] = { false };
    bool m_MouseButtonsLast[NUM_MOUSE_BUTTONS] = { false };

    glm::vec2 m_MousePosition = glm::vec2();
    glm::vec2 m_MousePositionLast = glm::vec2();

    glm::vec2 m_AbsScrollPosition = glm::vec2();
    glm::vec2 m_ScrollPosition = glm::vec2();

    DesktopInput();

    void Update();

    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void MousePositionCallback(GLFWwindow* window, double xPos, double yPos);
    static void MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
public:
    ~DesktopInput();

    void SetupKeyInputs(Display* display);

    const bool IsKey(int keycode) const { return m_Keys[keycode]; }
    const bool IsKeyDown(int keycode) const { return m_Keys[keycode] && !m_KeysLast[keycode]; }
    const bool IsKeyUp(int keycode) const { return !m_Keys[keycode] && m_KeysLast[keycode]; }

    const bool IsMouseButton(int button) const { return m_MouseButtons[button]; }
    const bool IsMouseButtonDown(int button) const { return m_MouseButtons[button] && !m_MouseButtonsLast[button]; }
    const bool IsMoueButtonUp(int button) const { return !m_MouseButtons[button] && m_MouseButtonsLast[button]; }

    const glm::vec2& GetMousePosition() const { return m_MousePosition; }
    const glm::vec2& GetScrollPosition() const { return m_ScrollPosition; }
    const glm::vec2& GetAbsScrollPosition() const { return m_AbsScrollPosition; }

    const glm::vec2 GetDeltaMousePosition() const { return m_MousePosition - m_MousePositionLast; }
};

class Input {

    friend class GameContext;
    friend class Display; 

public:
    DesktopInput StandardInput;

private:
    Input();

    void Update() { StandardInput.Update(); }
};