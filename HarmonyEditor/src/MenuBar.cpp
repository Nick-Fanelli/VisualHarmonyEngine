//
// Created by Nick Fanelli on 3/20/21.
//

#include "MenuBar.h"

#include <imguipch.h>

#include "Layers/ImGuiLayer.h"

namespace HarmonyEditor::Menubar {


    void DisplayMenubar(GLFWwindow* windowPtr) {

        ImGui::BeginMainMenuBar();

        if(ImGui::BeginMenu("Window")) {

            if(ImGui::BeginMenu("Layout Windows")) {

                if(ImGui::MenuItem("Demo Window", "", ImGuiLayer::s_DisplayDemoWindow))
                    ImGuiLayer::s_DisplayDemoWindow = !ImGuiLayer::s_DisplayDemoWindow;

                ImGui::EndMenu();
            }

            ImGui::EndMenu();

        }

        ImGui::EndMainMenuBar();

    }

}