#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLUT/glut.h>

#include <string>
#include <sstream>

#include "../Core/Log.h"

static const int MIN_FILTER = GL_LINEAR;
static const int MAG_FILTER = GL_LINEAR;

class Texture {

    GLuint m_TextureID;

    const char* m_Filepath;
    int m_Width, m_Height;

public: 
    Texture();

    void Initialize(const char* filepath, int width, int height);
    void Bind();
    void Unbind();

    const GLuint& GetTextureID() const { return m_TextureID; }
    const char* GetFilepath() const { return m_Filepath; }

    const int& GetWidth() const { return m_Width; }
    const int& GetHeight() const { return m_Height; }
};