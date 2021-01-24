#include "Utils.h"

namespace FileUtils {

    std::string ReadFile(std::string& filepath) {
        std::ifstream FileStream(filepath);
        std::string Result;
        std::string Line;

        while(std::getline(FileStream, Line)) {
            Result.append(Line).append("\n");
        }

        return Result;
    }

    std::string ReadFile(const char* filepath) {
        std::ifstream FileStream(filepath);
        std::string Result;
        std::string Line;

        while(std::getline(FileStream, Line)) {
            Result.append(Line).append("\n");
        }

        return Result;
    }

}

// GLM Operator Overloads

std::ostream &operator<< (std::ostream& out, const glm::vec2& vec) {
    out << "Vector2f[ "
        << "X: " << vec.x << ", Y: " << vec.y
        << " ]";

    return out;
}

std::ostream &operator<< (std::ostream& out, const glm::vec3& vec) {
    out << "Vector3f[ "
        << "X: " << vec.x << ", Y; " << vec.y << ", Z: " << vec.z
        << " ]";

    return out;
}

std::ostream &operator<< (std::ostream& out, const glm::vec4& vec) {
    out << "Vector3f[ "
        << "X: " << vec.x << ", Y; " << vec.y << ", Z: " << vec.z << ", W: " << vec.w
        << " ]";

    return out;
}