//
// Created by Nick Fanelli on 3/29/21.
//

#include "Settings.h"

namespace HarmonyEditor {

    using namespace HarmonyEngine;

#ifdef __APPLE__
    static const char* s_SaveLocation = "HarmonySettings.json";
#else
    static const char* s_SaveLocation = "";
#endif

    nlohmann::json Settings::s_JsonValue = nlohmann::json();

    void Settings::LoadSettings() {
        if(!FileUtils::FileExists(s_SaveLocation))
            return;

        Log::Info("Reading Settings File...");
        s_JsonValue = nlohmann::json::parse(FileUtils::ReadFile(s_SaveLocation));
    }

    void Settings::SaveSettings() {
        Log::Info("Saving Settings File...");
        FileUtils::SaveFile(s_SaveLocation, s_JsonValue.dump());
    }

    void Settings::Set(const char* setting, const char* data) {
        s_JsonValue[setting] = data;
    }

    void Settings::SetAndSave(const char* setting, const char* data) {
        s_JsonValue[setting] = data;
        Settings::SaveSettings();
    }

    nlohmann::basic_json<>& Settings::Get(const char* setting) {
        return s_JsonValue[setting];
    }

    void Settings::Print() {
        std::cout << s_JsonValue.dump() << std::endl;
    }


}
