#include "core/app.h"

int App::run()
{
    if (this->init() == false) {
        return -1;
    }

    SDL_Event event;

    unsigned start    = SDL_GetTicks();
    unsigned previous = start;
    unsigned lag      = 0;

    while (this->isRunning) {
        unsigned current = SDL_GetTicks();
        unsigned elapsed = current - previous;
        previous         = current;
        lag += elapsed;

        while (SDL_PollEvent(&event)) {
            this->handleEvent(&event);
        }

        if (this->msPerUpdate > 0) {
            while (lag >= this->msPerUpdate) {
                this->update();
                lag -= this->msPerUpdate;
            }
        } else {
            while (lag >= this->msPerMouseUpdate) {
                this->updateMouse();
                lag -= this->msPerMouseUpdate;
            }
        }

        this->render();

        unsigned frameTime = SDL_GetTicks() - current;
        if (this->msPerFrame > frameTime) {
            SDL_Delay(this->msPerFrame - frameTime);
        }
    }

    this->clean();

    return 0;
}