//
// Created by Nick Fanelli on 3/29/21.
//

#pragma once

#include <harmonypch.h>
#include <json/json.hpp>

namespace HarmonyEditor {

    using namespace HarmonyEngine;

    class Settings {

    private:

        static nlohmann::json s_JsonValue;

    public:

        static void LoadSettings();
        static void SaveSettings();

        static void Set(const char* setting, const char* data);
        static void SetAndSave(const char* setting, const char* data);
        static nlohmann::basic_json<>& Get(const char* setting);

        static void Print();
    };
}