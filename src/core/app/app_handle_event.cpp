#include "SDL_events.h"
#include "SDL_keycode.h"
#include "core/app.h"
#include "core/config.h"

void App::handleEvent(SDL_Event *event)
{
    if (event->type == SDL_EventType::SDL_QUIT) {
        this->logger->log("App::handleEvent", "Catching Exit event", Logger::LogLevel::INFO);
        this->isRunning = false;
    } else if (event->type == SDL_EventType::SDL_KEYDOWN) {
        if (event->key.keysym.sym == SDLK_r) {
            this->logger->log("App::handleEvent", "Catching Restart event", Logger::LogLevel::INFO);
            this->initBoard();
        } else if (event->key.keysym.sym == SDLK_ESCAPE) {
            this->logger->log("App::handleEvent", "Catching Exit event", Logger::LogLevel::INFO);
            this->isRunning = false;
        } else if (event->key.keysym.sym == SDLK_p) {
            this->logger->log("App::handleEvent", "Catching Pause event", Logger::LogLevel::INFO);

            if (this->prevUps == 0) {
                this->prevUps = this->ups;
                this->updateUps(0);
            } else {
                this->updateUps(this->prevUps);
                this->prevUps = 0;
            }
        } else if (event->key.keysym.sym == SDLK_j) {
            this->logger->log("App::handleEvent", "Catching Slow event", Logger::LogLevel::INFO);
            this->updateUps(this->ups - Config::upsStep);
            this->prevUps = 0;
        } else if (event->key.keysym.sym == SDLK_k) {
            this->logger->log("App::handleEvent", "Catching Speed event", Logger::LogLevel::INFO);
            this->updateUps(this->ups + Config::upsStep);
            this->prevUps = 0;
        } else if (event->key.keysym.sym == SDLK_l && this->msPerUpdate == 0) {
            this->logger->log("App::handleEvent", "Catching Step event", Logger::LogLevel::INFO);
            this->update();
        } else if (event->key.keysym.sym == SDLK_i && this->msPerUpdate == 0) {
            this->logger->log("App::handleEvent", "Catching Shrinking Cell Size event", Logger::LogLevel::INFO);
            this->updateCellSize(this->cellSize - 2);
        } else if (event->key.keysym.sym == SDLK_o && this->msPerUpdate == 0) {
            this->logger->log("App::handleEvent", "Catching Enlarging Cell Size event", Logger::LogLevel::INFO);
            this->updateCellSize(this->cellSize + 2);
        }
    } else if (event->type == SDL_EventType::SDL_MOUSEBUTTONDOWN) {
        if (event->button.button == SDL_BUTTON_LEFT) {
            this->logger->log("App::handleEvent", "Catching Birth event", Logger::LogLevel::INFO);
            this->placeMode = 1;
        } else if (event->button.button == SDL_BUTTON_RIGHT) {
            this->logger->log("App::handleEvent", "Catching Unalive event", Logger::LogLevel::INFO);
            this->placeMode = -1;
        }
    } else if (event->type == SDL_EventType::SDL_MOUSEBUTTONUP) {
        if ((event->button.button == SDL_BUTTON_LEFT && this->placeMode == 1)
            || (event->button.button == SDL_BUTTON_RIGHT && this->placeMode == -1)) {
            this->logger->log("App::handleEvent", "Catching Stop Mouse vent", Logger::LogLevel::INFO);
            this->placeMode = 0;
        }
    }
}