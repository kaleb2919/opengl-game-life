#pragma once
#include <glm/vec3.hpp>

enum ECellType
{
    DEAD = 0,
    ALIVE,
};

struct Cell
{
    glm::vec3 color = glm::vec3(255);
    ECellType type = DEAD;
};

class Field
{
    int width;
    int height;

    Cell* field;

public:

    Field(int width, int height);

    void nextLifeStep();
    int countNearCellByType(int x, int y, ECellType type);
    Cell& getCell(int x, int y);
    void switchCellAtCursor(int x, int y);
};
