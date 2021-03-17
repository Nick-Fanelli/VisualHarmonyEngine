//
// Created by Nick Fanelli on 3/16/21.
//

#include "ImGuiLayer.h"

void ApplyDefaultTheme() {
    ImGuiStyle& style = ImGui::GetStyle();

    ImVec4 themeTextColor = ImVec4(1, 1, 1, 1);

    ImVec4 themeBackgroundColor = ImVec4(0.235, 0.247, 0.254, 1);
    ImVec4 themeChildBackgroundColor = ImVec4(0.169, 0.169, 0.169, 1);
    ImVec4 themeChildBackgroundHoverColor = ImVec4(0.21, 0.21, 0.21, 1);
    ImVec4 themeChildBackgroundActiveColor = ImVec4(0.23, 0.23, 0.23, 1);

    ImVec4 themeAccentColor = ImVec4(0.2705882353, 0.8196078431, 0.4156862745, 1);
    ImVec4 themeAccentHoverColor = ImVec4(0.4, 0.9490196078, 0.5450980392, 1);

    style.Colors[ImGuiCol_Text]                 = themeTextColor;
    style.Colors[ImGuiCol_TextDisabled]         = ImVec4(0.60f, 0.60f, 0.60f, 1);
    style.Colors[ImGuiCol_TextSelectedBg]       = themeAccentColor;

    style.Colors[ImGuiCol_WindowBg]             = themeBackgroundColor;
    style.Colors[ImGuiCol_ChildBg]              = themeChildBackgroundColor;
    style.Colors[ImGuiCol_PopupBg]              = ImVec4(themeBackgroundColor.x, themeBackgroundColor.y, themeBackgroundColor.z, 0.94f);

    style.Colors[ImGuiCol_Border]                = themeBackgroundColor;
    style.Colors[ImGuiCol_BorderShadow]          = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);

    style.Colors[ImGuiCol_FrameBg]               = themeChildBackgroundColor;
    style.Colors[ImGuiCol_FrameBgHovered]        = themeChildBackgroundHoverColor;
    style.Colors[ImGuiCol_FrameBgActive]         = themeChildBackgroundActiveColor;

    style.Colors[ImGuiCol_TitleBg]               = themeChildBackgroundColor;
    style.Colors[ImGuiCol_TitleBgActive]         = themeChildBackgroundColor;
    style.Colors[ImGuiCol_TitleBgCollapsed]      = themeBackgroundColor;

    style.Colors[ImGuiCol_MenuBarBg]             = themeChildBackgroundColor;

    style.Colors[ImGuiCol_ScrollbarGrab]         = themeBackgroundColor;
    style.Colors[ImGuiCol_ScrollbarGrabHovered]  = themeBackgroundColor;
    style.Colors[ImGuiCol_ScrollbarBg]           = themeChildBackgroundColor;
    style.Colors[ImGuiCol_ScrollbarGrabActive]   = themeChildBackgroundActiveColor;

    style.Colors[ImGuiCol_CheckMark]             = themeAccentColor;

    style.Colors[ImGuiCol_SliderGrab]            = themeBackgroundColor;
    style.Colors[ImGuiCol_SliderGrabActive]      = themeChildBackgroundHoverColor;

    style.Colors[ImGuiCol_Button]                = themeChildBackgroundColor;
    style.Colors[ImGuiCol_ButtonHovered]         = themeChildBackgroundHoverColor;
    style.Colors[ImGuiCol_ButtonActive]          = themeChildBackgroundActiveColor;

    style.Colors[ImGuiCol_Header]                = themeChildBackgroundColor;
    style.Colors[ImGuiCol_HeaderHovered]         = themeChildBackgroundHoverColor;
    style.Colors[ImGuiCol_HeaderActive]          = themeChildBackgroundActiveColor;

    style.Colors[ImGuiCol_ResizeGrip]            = themeChildBackgroundColor;
    style.Colors[ImGuiCol_ResizeGripHovered]     = themeChildBackgroundHoverColor;
    style.Colors[ImGuiCol_ResizeGripActive]      = themeChildBackgroundActiveColor;

    style.Colors[ImGuiCol_PlotLines]             = themeAccentColor;
    style.Colors[ImGuiCol_PlotLinesHovered]      = themeAccentHoverColor;
    style.Colors[ImGuiCol_PlotHistogram]         = themeAccentColor;
    style.Colors[ImGuiCol_PlotHistogramHovered]  = themeAccentHoverColor;

    style.Colors[ImGuiCol_Tab]                    = ImLerp(style.Colors[ImGuiCol_Header],       style.Colors[ImGuiCol_TitleBgActive], 0.90f);
    style.Colors[ImGuiCol_TabHovered]             = style.Colors[ImGuiCol_HeaderHovered];
    style.Colors[ImGuiCol_TabActive]              = themeAccentColor;
    style.Colors[ImGuiCol_TabUnfocused]           = ImLerp(style.Colors[ImGuiCol_Tab],          style.Colors[ImGuiCol_TitleBg], 0.80f);
    style.Colors[ImGuiCol_TabUnfocusedActive]     = ImLerp(style.Colors[ImGuiCol_TabActive],    style.Colors[ImGuiCol_TitleBg], 0.40f);

}

void ImGuiLayer::Initialize(GameContext* gameContextPtr) {

    const char* glsl_version = "#version 150";

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void) io;

    ApplyDefaultTheme();

//    ImGui::StyleColorsDark();
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);

    ImGui_ImplGlfw_InitForOpenGL(gameContextPtr->GetDisplay().GetWindowPointer(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);

}

void ImGuiLayer::RenderImGuiWindows() {
    // Start ImGui Frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Do Stuff
    ImGui::ShowDemoWindow();

//    ImGui::Begin("Inspector");
////    ImGui::ColorEdit3("Quad Color", &s_QuadRenderer->Color.r, ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB);
//    ImGui::End();

    // End ImGui Frame
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::CleanUp() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}