//
// Created by Nick Fanelli on 3/20/21.
//

#include "MenuBar.h"

#include <harmonypch.h>
#include <imguipch.h>

#include "Layers/ImGuiLayer.h"

#define _WIN32 // For Testing

namespace HarmonyEditor::Menubar {

#ifdef _WIN32

    void DisplayMenubar() {

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

#elif defined __APPLE__

    void DisplayMenubar() {



    }

#endif

}