#include "Image.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Image::Image(const char* file_name)
{
    int width, height, channels;

    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load(file_name, &width, &height, &channels, 0);
    if (data)
    {

        if (channels == 4)
        {
            internal_format = GL_RGBA8;
            data_format = GL_RGBA;
        }
        else if (channels == 3)
        {
            internal_format = GL_RGB8;
            data_format = GL_RGB;
        }
        else if (channels == 1)
        {
            internal_format = GL_R8;
            data_format = GL_R8;
        }
        else
        {
            std::cout << "Texture Format Not Supported, Channels: " << channels << std::endl;
        }

        load(width, height, data);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
        stbi_image_free(data);
    }

}

Image::Image(GLint width, GLint height, unsigned char* data)
{
    load(width, height, data);
}

GLuint Image::getDescriptor()
{
    return descriptor;
}

void Image::reload(GLint width, GLint height, unsigned char* data)
{
    glDeleteTextures(1, &descriptor);
    load(width, height, data);
}

void Image::load(GLint width, GLint height, unsigned char* data)
{
    glCreateTextures(GL_TEXTURE_2D, 1, &descriptor);

    glTextureStorage2D(descriptor, 1, internal_format, width, height);
    glTextureSubImage2D(descriptor, 0, 0, 0, width, height, data_format, GL_UNSIGNED_BYTE, data);
    glGenerateTextureMipmap(GL_TEXTURE_2D);
    glTextureParameteri(descriptor, GL_TEXTURE_WRAP_S, texture_wrap);
    glTextureParameteri(descriptor, GL_TEXTURE_WRAP_T, texture_wrap);
    glTextureParameteri(descriptor, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(descriptor, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
