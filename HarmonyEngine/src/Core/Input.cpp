#include "Input.h"
#include <iostream>

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

void DesktopInput::AddKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    for(DesktopInput* desktopInput : s_Instances) {
        desktopInput->keys[key] = action != GLFW_RELEASE;
    }
}

void DesktopInput::SetupKeyInputs(Display* display) {
    glfwSetKeyCallback(display->GetWindowPointer(), DesktopInput::AddKeyCallback);
}