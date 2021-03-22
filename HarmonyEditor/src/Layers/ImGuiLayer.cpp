//
// Created by Nick Fanelli on 3/16/21.
//

#include "ImGuiLayer.h"

#include "../Theme.h"
#include "../MenuBar.h"

namespace HarmonyEditor {

    static GameContext* s_GameContextPtr = nullptr;
    float ImGuiLayer::s_Time = 0.0f;

    static void ApplySelectedTheme() {
        ImGuiStyle& style = ImGui::GetStyle();

        Theme::ThemeData themeData = Theme::GetTheme(Theme::s_ThemeType[Theme::s_SelectedTheme]);


        style.Colors[ImGuiCol_Text] = themeData.TextColor;
        style.Colors[ImGuiCol_TextSelectedBg] = themeData.AccentColor;

        float disableColor = Theme::s_SelectedTheme == 0 ? 0.6f : 0.4f;
        style.Colors[ImGuiCol_TextDisabled] = ImVec4(disableColor, disableColor, disableColor, 1); // Todo: Become Dynamic

        style.Colors[ImGuiCol_WindowBg] = themeData.BackgroundColor;
        style.Colors[ImGuiCol_ChildBg] = themeData.BackgroundColor;
        style.Colors[ImGuiCol_PopupBg] = ImVec4(themeData.ChildBackgroundColor.x, themeData.ChildBackgroundColor.y, themeData.ChildBackgroundColor.z, 1);
        style.Colors[ImGuiCol_DockingPreview] = themeData.AccentColor;

        style.Colors[ImGuiCol_Separator] = themeData.SeparatorColor;
        style.Colors[ImGuiCol_SeparatorActive] = themeData.SeparatorHoverColor;
        style.Colors[ImGuiCol_SeparatorHovered] = themeData.SeparatorHoverColor;

        style.Colors[ImGuiCol_Border] = themeData.BackgroundColor;
        style.Colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);

        style.Colors[ImGuiCol_FrameBg] = themeData.ChildBackgroundColor;
        style.Colors[ImGuiCol_FrameBgHovered] = themeData.ChildBackgroundHoverColor;
        style.Colors[ImGuiCol_FrameBgActive] = themeData.ChildBackgroundActiveColor;

        style.Colors[ImGuiCol_TitleBg] = themeData.ChildBackgroundColor;
        style.Colors[ImGuiCol_TitleBgActive] = themeData.ChildBackgroundColor;
        style.Colors[ImGuiCol_TitleBgCollapsed] = themeData.BackgroundColor;

        style.Colors[ImGuiCol_MenuBarBg] = themeData.ChildBackgroundColor;

        style.Colors[ImGuiCol_ScrollbarGrab] = themeData.BackgroundColor;
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = themeData.BackgroundColor;
        style.Colors[ImGuiCol_ScrollbarBg] = themeData.ChildBackgroundColor;
        style.Colors[ImGuiCol_ScrollbarGrabActive] = themeData.ChildBackgroundActiveColor;

        style.Colors[ImGuiCol_CheckMark] = themeData.AccentColor;

        style.Colors[ImGuiCol_SliderGrab] = themeData.BackgroundColor;
        style.Colors[ImGuiCol_SliderGrabActive] = themeData.ChildBackgroundHoverColor;

        style.Colors[ImGuiCol_Button] = themeData.ChildBackgroundColor;
        style.Colors[ImGuiCol_ButtonHovered] = themeData.ChildBackgroundHoverColor;
        style.Colors[ImGuiCol_ButtonActive] = themeData.ChildBackgroundActiveColor;

        style.Colors[ImGuiCol_Header] = themeData.ChildBackgroundColor;
        style.Colors[ImGuiCol_HeaderHovered] = themeData.ChildBackgroundHoverColor;
        style.Colors[ImGuiCol_HeaderActive] = themeData.ChildBackgroundActiveColor;

        style.Colors[ImGuiCol_ResizeGrip] = themeData.ChildBackgroundColor;
        style.Colors[ImGuiCol_ResizeGripHovered] = themeData.ChildBackgroundHoverColor;
        style.Colors[ImGuiCol_ResizeGripActive] = themeData.ChildBackgroundActiveColor;

        style.Colors[ImGuiCol_PlotLines] = themeData.AccentColor;
        style.Colors[ImGuiCol_PlotLinesHovered] = themeData.AccentHoverColor;
        style.Colors[ImGuiCol_PlotHistogram] = themeData.AccentColor;
        style.Colors[ImGuiCol_PlotHistogramHovered] = themeData.AccentHoverColor;

        style.Colors[ImGuiCol_Tab] = ImLerp(style.Colors[ImGuiCol_Header], style.Colors[ImGuiCol_TitleBgActive], 0.90f);
        style.Colors[ImGuiCol_TabHovered] = style.Colors[ImGuiCol_HeaderHovered];
        style.Colors[ImGuiCol_TabActive] = themeData.ChildBackgroundActiveColor;
        style.Colors[ImGuiCol_TabUnfocused] = ImLerp(style.Colors[ImGuiCol_Tab], style.Colors[ImGuiCol_TitleBg], 0.80f);
        style.Colors[ImGuiCol_TabUnfocusedActive] = ImLerp(style.Colors[ImGuiCol_TabActive],
                                                           style.Colors[ImGuiCol_TitleBg], 0.40f);
    }

    void ImGuiLayer::Initialize(GameContext* gameContextPtr) {

        s_GameContextPtr = gameContextPtr;

        const char* glsl_version = "#version 150";

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();

        io.DisplaySize = ImVec2((float) gameContextPtr->GetDisplay().GetWidth(),
                                (float) gameContextPtr->GetDisplay().GetHeight());
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
//    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ApplySelectedTheme();

//    ImGui::StyleColorsDark();
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);

        ImGui_ImplGlfw_InitForOpenGL(gameContextPtr->GetDisplay().GetWindowPointer(), true);
        ImGui_ImplOpenGL3_Init(glsl_version);
    }

    static void DrawDockSpace() {
        int windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
                          ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                          ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);
        ImGui::SetNextWindowSize(s_GameContextPtr->GetDisplay().GetImGuiSize());

        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

        static bool s_Show = true;

        ImGui::Begin("Dockspace", &s_Show, windowFlags);
        ImGui::PopStyleVar(3);
        ImGui::DockSpace(ImGui::GetID("Dockspace"));
        ImGui::End();
    }

    static void DrawSettingPanel() {
        ImGui::Begin("Settings");

        ImGui::BeginChild("Settings Items");

        if(ImGui::CollapsingHeader("Editor")) {

            if(ImGui::Combo("Theme", &Theme::s_SelectedTheme, Theme::s_ThemeType, IM_ARRAYSIZE(Theme::s_ThemeType))) {
                ApplySelectedTheme();
            }

        }

        ImGui::EndChild();

        ImGui::End();
    }

    void ImGuiLayer::RenderImGuiWindows() {
        // Start ImGui Frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Do Stuff
        DrawDockSpace();
        ImGui::ShowDemoWindow();
        DrawSettingPanel();

//        Menubar::DisplayMenubar();

//    ImGui::Begin("Inspector");
//    ImGui::ColorEdit3("Quad Color", &s_QuadRenderer->Color.r, ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB);
//    ImGui::End();

        // End ImGui Frame
        ImGui::Render();
        ImGui::UpdatePlatformWindows();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::CleanUp() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

}