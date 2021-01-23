#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLUT/glut.h>

#include <stb_image.h>
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
    Texture(const char* filepath, int width, int height) 
        : m_Filepath(filepath), m_Width(width), m_Height(height) {}

    void Initialize() {
        // Generate Texture on GPU
        glGenTextures(1, &m_TextureID);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);

        // Setup Image Parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MIN_FILTER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, MAG_FILTER);

        // Setup STB_Image
        stbi_set_flip_vertically_on_load(true);

        int channels;

        stbi_uc* image = stbi_load(m_Filepath, &m_Width, &m_Height, &channels, 0); // Load the image

        if(image != nullptr) {
            if(channels == 3) { // RGB Channels
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
            } else if(channels == 4) { // RBGA Channels
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
            } else {
                std::stringstream errorMessage;
                errorMessage << "Could not load image " << m_Filepath << ", with unknown number of channels : " << channels;
                // Log::Error(errorMessage);
            }

            stbi_image_free(image);
        }

        Unbind();
    }

    void Bind() {
        if(m_TextureID == -1) {
            Log::Warn("Texture ID of image '" + std::string(m_Filepath) + "' holds a textureID pointer of -1!\n" +
            "\tThis may result in the texture not binding or an OpenGL error!!\n" +
            "\tThe textureID pointer should hold the memory location of the texture!");
        }

        glBindTexture(GL_TEXTURE_2D, m_TextureID);
    }

    void Unbind() {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    const GLuint& GetTextureID() const { return m_TextureID; }
    const char* GetFilepath() const { return m_Filepath; }

    const int& GetWidth() const { return m_Width; }
    const int& GetHeight() const { return m_Height; }
};