#pragma once

#include "SDL_events.h"
#include "SDL_pixels.h"
#include "SDL_render.h"
#include "SDL_ttf.h"
#include "helper/logger.h"

#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>

class App
{
  private:
    int cellSize;
    int mouseUps;
    int ups;
    int fps;

    int prevUps = 0;

    double msPerMouseUpdate;
    double msPerUpdate;
    double msPerFrame;

    bool isRunning = false;

    SDL_Window   *gWindow   = nullptr;
    SDL_Renderer *gRenderer = nullptr;
    TTF_Font     *font      = nullptr;

    std::vector<std::vector<bool>> cells;
    std::vector<std::vector<bool>> cells2;

    bool currentCellArray;

    int score = 0;
    int best  = 0;

    Logger *logger = nullptr;

    int gridStartX = 0;
    int gridStartY = 0;
    int gridEndX   = 0;
    int gridEndY   = 0;
    int gridSizeH  = 0;
    int gridSizeW  = 0;

    int placeMode = 0;

    void                renderCellGrid(std::vector<std::vector<bool>> *array);
    void                renderCell(int x, int y, bool isAlive);
    void                renderNavBar();
    std::pair<int, int> renderText(
        std::string msg,
        int         x,
        int         y,
        SDL_Color   fg,
        SDL_Color   bg,
        bool        isCenteredX = false,
        bool        isCenteredY = false);

    void initBoard();
    void placeCell(int x, int y);

    void updateUps(int value);
    void updateFps(int value);
    void updateMouseUps(int value);
    void updateCellSize(int value);
    void updateCellArraySize(int prevW, int prevH, std::vector<std::vector<bool>> *firstArray, std::vector<std::vector<bool>> *secondArray);

    std::pair<int, int> cellCount();

    void aaFilledTrigonColor(int x1, int y1, int x2, int y2, int x3, int y3, SDL_Color color);
    void aaFilledRectangleColor(int x1, int y1, int x2, int y2, SDL_Color color);

    void nextGeneration(std::vector<std::vector<bool>> *firstArray, std::vector<std::vector<bool>> *secondArray);
    int  livingNeighbors(std::vector<std::vector<bool>> *array, int x, int y);

  public:
    App(Logger *logger, int ups = 1, int mouseUps = 1000, int fps = -1);
    int  run();
    bool init();
    void handleEvent(SDL_Event *event);
    void update();
    void updateMouse();
    void render();
    void clean();
};