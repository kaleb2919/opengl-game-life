#include <iostream>

#include "Screen.h"
#include "Window.h"
#include "Shader.h"

int main()
{
    int width_window = 1280;
    int height_window = 720;

    auto window = new Window(width_window, height_window, "Some window");

    auto shader = new Shader();
    if (!shader->loadShaders("shader.vert", "shader.frag"))
    {
        std::cout << "Failed to load shaders" << std::endl;
        return 1;
    }

    int width_screen = width_window / 16;
    int height_screen = height_window / 16;

    auto screen = Screen(height_screen, width_screen, shader);

    double cursor_X = width_screen / 2;
    double cursor_Y = height_screen / 2;

    bool space_pressed = false;
    bool enter_pressed = false;

    int control_speed = 10;

    double sim_delay = 0.08f;
    double sim_timer = 0.0f;

    bool sim_enabled = false;

    while (window->isRunning())
    {
        window->processInput();
        window->clear();
        double delta_time = window->getDeltaTime();
        double delta_move = control_speed * delta_time;

        if (window->isKeyPress(KEY_UP))
        {
            cursor_Y += delta_move;
        }
        if (window->isKeyPress(KEY_DOWN))
        {
            cursor_Y -= delta_move;
        }
        if (window->isKeyPress(KEY_RIGHT))
        {
            cursor_X += delta_move;
        }
        if (window->isKeyPress(KEY_LEFT))
        {
            cursor_X -= delta_move;
        }
        if (window->isKeyPress(KEY_SPACE) && !space_pressed)
        {
            screen.switchCellAtCursor();
            space_pressed = true;
        }
        if (window->isKeyPress(KEY_ENTER) && !enter_pressed)
        {
            sim_enabled = !sim_enabled;
            enter_pressed = true;
        }
        if (window->isKeyRelease(KEY_SPACE) && space_pressed)
        {
            space_pressed = false;
        }
        if (window->isKeyRelease(KEY_ENTER) && enter_pressed)
        {
            enter_pressed = false;
        }

        cursor_X = cursor_X < 0 ? width_screen : cursor_X;
        cursor_Y = cursor_Y < 0 ? height_screen : cursor_Y;

        screen.moveCursor(cursor_X, cursor_Y);

        if (sim_enabled)
        {
            if (sim_timer <= 0)
            {
                screen.nextLifeStep();
                sim_timer = sim_delay;
            }
            else
            {
                sim_timer -= delta_time;
            }
        }

        screen.draw();
        window->swap();
    }
}
