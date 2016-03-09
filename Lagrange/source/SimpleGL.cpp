#include <atlas/utils/Application.hpp>
#include "LagrangeScene.hpp"

int main()
{
    // Create a new window (only one per application for now).
    APPLICATION.createWindow(1000, 500, "Simple GL");

    // Now give it our scene.
    APPLICATION.addScene(new LagrangeScene);
    
    // Finally, run the application.
    APPLICATION.runApplication();

    return 0;
}