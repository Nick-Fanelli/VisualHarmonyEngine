#pragma once

#include "harmonypch.h"

namespace HarmonyEngine {

    std::ostream& operator<<(std::ostream& out, const entt::entity& entity);

    namespace FileUtils {
        std::string ReadFile(const char* filepath);
        std::string ReadFile(const std::string& filepath);

        void SaveFile(const char* filepath, const char* fileData);
        void SaveFile(const char* filepath, const std::string& fileData);

        void CreateFile(const char* filepath);

        bool FileExists(const char* filepath);
    }

    namespace OpenGLUtils {
        int GetGPUMaxTextureSlots();

        // GLM Operator Overloads
        std::ostream& operator<<(std::ostream& out, const glm::vec2& vec);
        std::ostream& operator<<(std::ostream& out, const glm::vec3& vec);
        std::ostream& operator<<(std::ostream& out, const glm::vec4& vec);
    }
}