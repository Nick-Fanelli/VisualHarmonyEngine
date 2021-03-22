//
// Created by Nick Fanelli on 3/20/21.
//

#include "MenuBar.h"

#include <harmonypch.h>
#include <imguipch.h>

namespace HarmonyEditor::Menubar {

#ifdef _WIN32

    void DisplayMenubar() {

        ImGui::BeginMainMenuBar();

        if(ImGui::BeginMenu("File")) {

            ImGui::MenuItem("Test");

            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("Edit")) {

            ImGui::EndMenu();
        }


        ImGui::EndMainMenuBar();

    }

#elif defined __APPLE__

    void DisplayMenubar() {



    }

#endif

}