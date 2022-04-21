#pragma once

#include <vector>
#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "Field.h"
#include "Shader.h"
#include "Image.h"

struct Vertex
{
    glm::vec3 position;
    glm::vec2 texture_coordinate;
};
struct Cursor
{
    glm::vec2 position = glm::vec3(0);
    glm::vec3 color = glm::vec3(255);
};


class Screen
{
    std::vector<Vertex> vertices = {
        {glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
        {glm::vec3(1.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
        {glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
        {glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)}
    };

    std::vector<GLuint> indices = { 0, 1, 3, 1, 2, 3 };

    GLuint VAO, VBO, EBO;

    GLint width;
    GLint height;

    unsigned char* buffer;

    Field* field;
    Image* image;
    Shader* shader;

    Cursor cursor;

    void setup();
public:

    Screen(GLint height, GLint width, Shader* shader);
    void draw();
    void clear();
    void renderField();

    void nextLifeStep();
    void moveCursor(int x, int y);
    void set(int x, int y, glm::vec3 color);
    void switchCellAtCursor();
};
