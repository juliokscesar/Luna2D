#include <iostream>

#include "Core/Remus.hpp"
#include "Application.hpp"

int main()
{
    Remus::Application *app = new Remus::Application();

    if (app->Init() != REMUS_INIT_SUCCESS)
        return -1;

    app->Run();

    delete app;
}
