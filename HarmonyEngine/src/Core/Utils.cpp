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