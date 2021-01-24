#include "Input.h"
#include <iostream>
#include <stdio.h>

Input::Input() : StandardInput(DesktopInput()) {

}

// =================================================================
// Desktop Input
// =================================================================

std::vector<DesktopInput*> DesktopInput::s_Instances;

DesktopInput::DesktopInput() {
    s_Instances.push_back(this);
}

DesktopInput::~DesktopInput() {
    s_Instances.erase(std::remove(s_Instances.begin(), s_Instances.end(), this), s_Instances.end());
}

void DesktopInput::Update() {
    memcpy(&m_KeysLast, &m_Keys, sizeof(m_KeysLast));
    memcpy(&m_MouseButtonsLast, & m_MouseButtons, sizeof(m_MouseButtonsLast));

    memcpy(&m_MousePositionLast, &m_MousePosition, sizeof(m_MousePositionLast));

    m_ScrollPosition = { 0, 0 };
}

void DesktopInput::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    for(DesktopInput* desktopInput : s_Instances) {
        desktopInput->m_Keys[key] = action == GLFW_PRESS;
    }
}

void DesktopInput::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    for(DesktopInput* desktopInput : s_Instances) {
        desktopInput->m_MouseButtons[button] = action == GLFW_PRESS;
    }
}

void DesktopInput::MousePositionCallback(GLFWwindow* window, double xPos, double yPos) {
    for(DesktopInput* desktopInput : s_Instances) {
        desktopInput->m_MousePosition = { xPos, yPos };
    }
}

void DesktopInput::MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
    for(DesktopInput* desktopInput : s_Instances) {
        desktopInput->m_ScrollPosition = { xOffset, yOffset };
        desktopInput->m_AbsScrollPosition = { 
            desktopInput->m_AbsScrollPosition.x + xOffset, 
            desktopInput->m_AbsScrollPosition.y + yOffset 
        }; 
    }
}

void DesktopInput::SetupKeyInputs(Display* display) {
    glfwSetKeyCallback(display->GetWindowPointer(), DesktopInput::KeyCallback);
    glfwSetMouseButtonCallback(display->GetWindowPointer(), DesktopInput::MouseButtonCallback);
    glfwSetCursorPosCallback(display->GetWindowPointer(), DesktopInput::MousePositionCallback);
    glfwSetScrollCallback(display->GetWindowPointer(), DesktopInput::MouseScrollCallback);
}