#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <glm/glm.hpp>

namespace HarmonyEngine {

    namespace FileUtils {
        std::string ReadFile(const char* filepath);
    }

    namespace OpenGLUtils {
        int GetGPUMaxTextureSlots();

        // GLM Operator Overloads
        std::ostream& operator<<(std::ostream& out, const glm::vec2& vec);

        std::ostream& operator<<(std::ostream& out, const glm::vec3& vec);

        std::ostream& operator<<(std::ostream& out, const glm::vec4& vec);
    }
}