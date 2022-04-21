#pragma once

#include <iostream>

#include <glad/glad.h>

class Image
{
    GLuint descriptor;
    GLuint texture_wrap = GL_CLAMP_TO_EDGE;
    GLenum data_format = GL_RGB;
    GLenum internal_format = GL_RGB8;

public:
    Image(const char* file_name);
    Image(GLint width, GLint height, unsigned char* data);
    GLuint getDescriptor();
    void load(GLint width, GLint height, unsigned char* data);
    void reload(GLint width, GLint height, unsigned char* data);
};
