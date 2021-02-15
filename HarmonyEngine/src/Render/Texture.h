#pragma once

#include <GL/glew.h>
#include <GLUT/glut.h>

#include "../Core/Log.h"

static const int MIN_FILTER = GL_LINEAR;
static const int MAG_FILTER = GL_LINEAR;

class Texture {

    GLuint m_TextureID = -1;

    const char* m_Filepath = nullptr;
    int m_Width, m_Height;

public: 
    Texture(const char* filepath, int width, int height) 
        : m_Filepath(filepath), m_Width(width), m_Height(height) {}

    Texture() {}

    void Initialize();
    void Initialize(const char* filepath, int width, int height);
    void Bind();
    void Unbind();

    const GLuint& GetTextureID() const { return m_TextureID; }
    const char* GetFilepath() const { return m_Filepath; }

    const int& GetWidth() const { return m_Width; }
    const int& GetHeight() const { return m_Height; }
};