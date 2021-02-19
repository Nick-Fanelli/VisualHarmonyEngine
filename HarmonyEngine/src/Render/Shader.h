#pragma once

#include <GL/glew.h>
#include <GLUT/glut.h>

#include <string>
#include <unordered_map>
#include "../Core/Utils.h"

#include <glm/glm.hpp>

namespace HarmonyEngine {

    class Shader {

        GLuint m_ProgramID, m_VertexID, m_FragmentID;
        std::unordered_map<std::string, std::string>* m_Replacements;

        void AttachVertexShader(std::string& source);

        void AttachFragmentShader(std::string& source);

        void Link();

    public:
        static void Unbind();

        Shader() = default;

        Shader(const Shader&) = default;

        Shader(const char* vertexFilePath, const char* fragmentFilePath,
               std::unordered_map<std::string, std::string>* replacements = nullptr)
                : m_ProgramID(glCreateProgram()), m_Replacements(replacements) {

            std::string vertexSource = FileUtils::ReadFile(vertexFilePath);
            std::string fragmentSource = FileUtils::ReadFile(fragmentFilePath);

            AttachVertexShader(vertexSource);
            AttachFragmentShader(fragmentSource);
            Link();
        }

        void AddUniformVec4(const char* varName, const glm::vec4& vec4) const;

        void AddUniformVec3(const char* varName, const glm::vec3& vec3) const;

        void AddUniformMat4(const char* varName, const glm::mat4& mat4) const;

        void AddUniformInt(const char* varName, const int& integer) const;

        void AddUniformIntArray(const char* varName, const int& size, const int* array) const;

        void AddUniformUintArray(const char* varName, const int& size, const uint32_t* array) const;

        void Bind() const;

        void Dispose() const;
    };

}