#include "Application.h"

int main()
{
    Application app;

    while (app.isRunning())
    {
        // Frame start
        app.updateEvents();
        app.update();
        app.render();
        // Frame end
    }

    return 0;
}