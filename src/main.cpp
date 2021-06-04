#include "Application.h"

int main()
{
    Application app;

    while (app.IsRunning())
    {
        // Frame start
        app.UpdateEvents();
        app.Update();
        app.Render();
        // Frame end
    }

    return 0;
}