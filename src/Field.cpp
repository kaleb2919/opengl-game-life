#include "Field.h"
#include <utility>

Field::Field(int width, int height)
    : width(width), height(height)
{
    int field_size = height * width;
    field = new Cell[field_size];
}

void Field::nextLifeStep()
{
    Cell* temp_field = new Cell[width * height];
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            Cell& cell = getCell(x, y);
            int count = countNearCellByType(x, y, ALIVE);
            if (cell.type == DEAD && count == 3)
            {
                temp_field[x + y * width].type = ALIVE;
            }
            else if (cell.type == ALIVE && (count == 2 || count == 3))
            {
                temp_field[x + y * width].type = ALIVE;
            }
        }
    }

    std::swap<Cell*>(field, temp_field);
    delete [] temp_field;
}

int Field::countNearCellByType(int x, int y, ECellType type)
{
    int count = 0;

    int down = y - 1 < 0 ? height - 1 : y - 1;
    int up = y + 1 == height? 0 : y + 1;
    int left = x - 1 < 0 ? width - 1 : x - 1;
    int right = x + 1 == width ? 0 : x + 1;

    if (getCell(left, y).type == type)
        count++;
    if (getCell(right, y).type == type)
        count++;
    if (getCell(x, down).type == type)
        count++;
    if (getCell(x, up).type == type)
        count++;
    if (getCell(left, down).type == type)
        count++;
    if (getCell(right, up).type == type)
        count++;
    if (getCell(left, up).type == type)
        count++;
    if (getCell(right, down).type == type)
        count++;

    return count;
}

Cell& Field::getCell(int x, int y)
{
    int position = x + y * width;
    return field[position];
}

void Field::switchCellAtCursor(int x, int y)
{
    Cell& cell = getCell(x, y);
    if (cell.type == ALIVE)
        cell.type = DEAD;
    else
        cell.type = ALIVE;
}
