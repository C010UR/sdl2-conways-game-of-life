#include "core/app.h"

App::App(Logger *logger, int ups, int mouseUps, int fps)
{
    this->logger    = logger;
    this->isRunning = true;
    this->prevUps = ups;
    this->updateUps(0);
    this->updateFps(fps);
    this->updateMouseUps(mouseUps);
}