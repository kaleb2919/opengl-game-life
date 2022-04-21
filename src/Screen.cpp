#include "Screen.h"

#include <iostream>

Screen::Screen(GLint height, GLint width, Shader* shader)
    : width(width), height(height), shader(shader)
{
    int rgb_size = height * (width * 3);
    buffer = new unsigned char[rgb_size];

    field = new Field(width, height);
    image = new Image(width, height, buffer);

    setup();
}

void Screen::moveCursor(int x, int y)
{
    cursor.position.x = x % width;
    cursor.position.y = y % height;
}

void Screen::setup()
{
    glCreateBuffers(1, &VBO);
    glNamedBufferStorage(VBO, vertices.size() * sizeof(Vertex), &vertices[0], 0x0);

    glCreateBuffers(1, &EBO);
    glNamedBufferStorage(EBO, indices.size() * sizeof(unsigned int), &indices[0], 0x0);

    glCreateVertexArrays(1, &VAO);
    glVertexArrayVertexBuffer(VAO, 0, VBO, 0, sizeof(Vertex));
    glVertexArrayElementBuffer(VAO, EBO);

    glEnableVertexArrayAttrib(VAO, 0);
    glEnableVertexArrayAttrib(VAO, 1);
    glVertexArrayAttribFormat(VAO, 1, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, position));
    glVertexArrayAttribFormat(VAO, 1, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, texture_coordinate));
    glVertexArrayAttribBinding(VAO, 0, 0);
    glVertexArrayAttribBinding(VAO, 1, 0);
}

void Screen::draw()
{
    clear();
    set(cursor.position.x, cursor.position.y, cursor.color);
    renderField();
    image->reload(width, height, buffer);
    shader->setInt("u_texture", 0);
    glBindTextureUnit(0, image->getDescriptor());
    shader->use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void *)0);
    glBindVertexArray(0);
}

void Screen::clear()
{
    int rgb_size = height * (width * 3);
    for (int i = 0; i < rgb_size; i = i + 3)
    {
        buffer[i] = 0;
        buffer[i+1] = 0;
        buffer[i+2] = 0;
    }
}

void Screen::renderField()
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            if (field->getCell(x, y).type == ALIVE)
            {
                set(x, y, glm::vec3(200, 50, 20));
            }
        }
    }
}

void Screen::nextLifeStep()
{
    field->nextLifeStep();
}


void Screen::set(int x, int y, glm::vec3 color)
{
    int position = (x * 3) + (y * (width * 3));
    buffer[position] = color.r;
    buffer[position+1] = color.g;
    buffer[position+2] = color.b;
}

void Screen::switchCellAtCursor()
{
    field->switchCellAtCursor(cursor.position.x, cursor.position.y);
}
