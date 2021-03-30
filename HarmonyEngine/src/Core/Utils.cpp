#include "Utils.h"

#include <sys/stat.h>
#include <GL/glew.h>

namespace HarmonyEngine {

    std::ostream& operator<<(std::ostream& out, const entt::entity& entity) {
        return (out << static_cast<uint32_t>(entity));
    }

    namespace FileUtils {

        std::string ReadFile(const std::string& filepath) {
            std::ifstream FileStream(filepath);
            std::string Result;
            std::string Line;

            while (std::getline(FileStream, Line)) {
                Result.append(Line).append("\n");
            }

            return Result;
        }

        std::string ReadFile(const char* filepath) {
            std::ifstream FileStream(filepath);
            std::string Result;
            std::string Line;

            while (std::getline(FileStream, Line)) {
                Result.append(Line).append("\n");
            }

            return Result;
        }

        void SaveFile(const char* filepath, const char* fileData) {
            std::ofstream fileStream;
            fileStream.open(filepath);
            fileStream << fileData << std::endl;
            fileStream.close();
        }

        void SaveFile(const char* filepath, const std::string& fileData) {
            std::ofstream fileStream;
            fileStream.open(filepath);
            fileStream << fileData << std::endl;
            fileStream.close();
        }

        void CreateFile(const char* filepath) {
            std::ofstream file { filepath };
        }

        bool FileExists(const char* filepath) {
            struct stat buffer{};
            return (stat (filepath, &buffer) == 0);
        }

    }

    namespace OpenGLUtils {
        int GetGPUMaxTextureSlots() {
            int queryResult;
            glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &queryResult);
            return queryResult;
        }

        // GLM Operator Overloads
        std::ostream& operator<<(std::ostream& out, const glm::vec2& vec) {
            out << "Vector2f[ "
                << "X: " << vec.x << ", Y: " << vec.y
                << " ]";

            return out;
        }

        std::ostream& operator<<(std::ostream& out, const glm::vec3& vec) {
            out << "Vector3f[ "
                << "X: " << vec.x << ", Y; " << vec.y << ", Z: " << vec.z
                << " ]";

            return out;
        }

        std::ostream& operator<<(std::ostream& out, const glm::vec4& vec) {
            out << "Vector3f[ "
                << "X: " << vec.x << ", Y; " << vec.y << ", Z: " << vec.z << ", W: " << vec.w
                << " ]";

            return out;
        }
    }
}