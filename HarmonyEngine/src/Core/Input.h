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
    bool keys[NUM_KEYS];
    // bool keysLast[NUM_KEYS];

    bool mouseButtons[NUM_MOUSE_BUTTONS];
    // bool mouseButtonsLast[NUM_MOUSE_BUTTONS];

    const glm::vec2 mousePosition();
    const glm::vec2 mousePostionLast();
    const glm::vec2 scrollPostion();

    DesktopInput();

    static void AddKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
public:
    ~DesktopInput();
    // void AddKeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
    // void AddMousePositionCallback(GLFWwindow* window, double xPos, double yPos);

    void SetupKeyInputs(Display* display);

    const bool IsKey(int keycode) { return keys[keycode]; }
    // const bool IsKeyDown(int keycode) const { return keys[keycode] && !keysLast[keycode]; }
    // const bool IsKeyUp(int keycode) const { return !keys[keycode] && keysLast[keycode]; }

    const bool IsMouseButton(int button) const { return mouseButtons[button]; }
    // const bool IsMouseButtonDown(int button) const { return mouseButtons[button] && !mouseButtonsLast[button]; }
    // const bool IsMouseButtonUp(int button) const { return !mouseButtons[button] && mouseButtonsLast[button]; }
};

class Input {

    friend class GameContext;

public:
    DesktopInput StandardInput;

private:
    Input();
};