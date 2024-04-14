#include "SDL_mouse.h"
#include "core/app.h"
#include "core/config.h"
#include "helper/logger.h"

#include <iterator>
#include <utility>

void App::update()
{
    this->logger->log("App::update", "Updating cells", Logger::LogLevel::INFO);

    this->nextGeneration(
        this->currentCellArray ? &this->cells : &this->cells2,
        this->currentCellArray ? &this->cells2 : &this->cells);
        
    this->currentCellArray = !this->currentCellArray;
}

void App::nextGeneration(std::vector<std::vector<bool>> *firstArray, std::vector<std::vector<bool>> *secondArray)
{
    for (int y = 0; y < this->gridSizeH; y++) {
        for (int x = 0; x < this->gridSizeW; x++) {
            int livingNeighbors = this->livingNeighbors(firstArray, x, y);

            if (!(*firstArray)[y][x] && livingNeighbors == 3) {
                (*secondArray)[y][x] = true;
            } else if ((*firstArray)[y][x] && (livingNeighbors < 2 || livingNeighbors > 3)) {
                (*secondArray)[y][x] = false;
            } else {
                (*secondArray)[y][x] = (*firstArray)[y][x];
            }
        }
    }
}

int App::livingNeighbors(std::vector<std::vector<bool>> *array, int x, int y)
{
    int result = 0;

    // Top left corner
    if (x == 0 && y == 0) {
        result += (*array)[y][x + 1] + (*array)[y + 1][x + 1] + (*array)[y + 1][x];
    }
    // Bottom left corner
    else if (x == 0 && y == this->gridSizeH - 1) {
        result += (*array)[y][x + 1] + (*array)[y - 1][x] + (*array)[y - 1][x + 1];
    }
    // Top right corner
    else if (x == this->gridSizeW - 1 && y == 0) {
        result += (*array)[y][x - 1] + (*array)[y + 1][x] + (*array)[y + 1][x - 1];
    }
    // Bottom right corner
    else if (x == this->gridSizeW - 1 && y == this->gridSizeH - 1) {
        result += (*array)[y][x - 1] + (*array)[y - 1][x - 1] + (*array)[y - 1][x];
    }
    // Left edge, excluding corners
    else if (x == 0) {
        result += (*array)[y][x + 1] + (*array)[y + 1][x + 1] + (*array)[y + 1][x] + (*array)[y - 1][x]
                  + (*array)[y - 1][x + 1];
    }
    // Right edge, excluding corners
    else if (x == this->gridSizeW - 1) {
        result += (*array)[y][x - 1] + (*array)[y + 1][x - 1] + (*array)[y + 1][x] + (*array)[y - 1][x]
                  + (*array)[y - 1][x - 1];
    }
    // Top edge, excluding corners
    else if (y == 0) {
        result += (*array)[y][x + 1] + (*array)[y + 1][x + 1] + (*array)[y + 1][x] + (*array)[y][x - 1]
                  + (*array)[y + 1][x - 1];
    }
    // Bottom edge, excluding corners
    else if (y == this->gridSizeH - 1) {
        result += (*array)[y][x + 1] + (*array)[y - 1][x + 1] + (*array)[y - 1][x] + (*array)[y][x - 1]
                  + (*array)[y - 1][x - 1];
    }
    // All other cases (non-edge, non-corner cells)
    else {
        result += (*array)[y - 1][x - 1] + (*array)[y - 1][x] + (*array)[y - 1][x + 1] + (*array)[y][x - 1]
                  + (*array)[y][x + 1] + (*array)[y + 1][x - 1] + (*array)[y + 1][x] + (*array)[y + 1][x + 1];
    }

    return result;
}

void App::updateMouse()
{
    if (this->placeMode == 0) {
        return;
    }

    int mouseX, mouseY;

    SDL_GetMouseState(&mouseX, &mouseY);

    int actualGridEndX = this->gridStartX + gridSizeW * this->cellSize;
    int actualGridEndY = this->gridStartY + gridSizeH * this->cellSize;

    if (mouseX < this->gridStartX || mouseY < this->gridStartY || mouseX > actualGridEndX || mouseY > actualGridEndY) {
        return;
    }

    int x = ((mouseX - this->cellSize - this->gridStartX) / this->cellSize)
            + ((mouseX - this->gridStartX) % this->cellSize > 0 ? 1 : 0);
    int y = ((mouseY - this->cellSize - this->gridStartY) / this->cellSize)
            + ((mouseY - this->gridStartY) % this->cellSize > 0 ? 1 : 0);

    if (x < 0 || x >= this->gridSizeW || y < 0 || y >= this->gridSizeH) {
        this->logger->log("App::updateMouse", "Outside of the cell array bounds", Logger::LogLevel::ERROR);
        return;
    }

    if (this->currentCellArray) {
        this->cells[y][x] = this->placeMode > 0 ? true : false;
    } else {
        this->cells2[y][x] = this->placeMode > 0 ? true : false;
    }
}

std::pair<int, int> App::cellCount()
{
    int living = 0;
    int dead   = 0;

    for (unsigned y = 0; y < this->cells.size(); y++) {
        for (unsigned x = 0; x < this->cells[y].size(); x++) {
            if (this->cells[y][x]) {
                living++;
            } else {
                dead++;
            }
        }
    }

    return {living, dead};
}

void App::updateUps(int value)
{
    if (value < 0) {
        value = 0;
    }

    this->ups         = value;
    this->msPerUpdate = value == 0 ? 0 : 1000. / value;
}

void App::updateMouseUps(int value)
{
    if (value < 0) {
        value = 0;
    }

    this->mouseUps         = value;
    this->msPerMouseUpdate = value == 0 ? 0 : 1000. / value;
}

void App::updateFps(int value)
{
    if (value < 0) {
        value = 0;
    }

    this->fps        = value;
    this->msPerFrame = value == 0 ? 0 : 1000. / value;
}

void App::updateCellSize(int value)
{
    if (value <= 1) {
        value = 1;
    }

    this->cellSize = value;

    int prevGridSizeW = this->gridSizeW;
    int prevGridSizeH = this->gridSizeH;

    SDL_DisplayMode gDisplayMode;

    if (SDL_GetDesktopDisplayMode(0, &gDisplayMode) < 0) {
        this->logger->log("App::init", SDL_GetError(), Logger::LogLevel::ERROR);
        return;
    }

    this->gridSizeW = gDisplayMode.w / value;
    this->gridSizeH = (gDisplayMode.h - Config::navbarHeight) / value;

    this->gridStartX = (gDisplayMode.w - this->gridSizeW * value) / 2;
    this->gridEndX   = gridStartX + this->gridSizeW * value;

    this->gridStartY = Config::navbarHeight + (((gDisplayMode.h - Config::navbarHeight) - this->gridSizeH * value) / 2);
    this->gridEndY   = gridStartY + this->gridSizeH * value;

    this->updateCellArraySize(
        prevGridSizeW,
        prevGridSizeH,
        this->currentCellArray ? &this->cells : &this->cells2,
        this->currentCellArray ? &this->cells2 : &this->cells);
}

void App::updateCellArraySize(
    int                             prevW,
    int                             prevH,
    std::vector<std::vector<bool>> *firstArray,
    std::vector<std::vector<bool>> *secondArray)
{
    std::vector<std::vector<bool>> newCellArray(this->gridSizeH, std::vector<bool>(this->gridSizeW, false));

    int startW = (prevW - this->gridSizeW) / 2;
    int startH = (prevH - this->gridSizeH) / 2;

    int newStartW = std::max(-startW, 0);
    int newStartH = std::max(-startH, 0);

    startW = std::max(startW, 0);
    startH = std::max(startH, 0);

    int copyWidth  = std::min(this->gridSizeW, prevW);
    int copyHeight = std::min(this->gridSizeH, prevH);

    for (int i = 0; i < copyHeight; ++i) {
        for (int j = 0; j < copyWidth; ++j) {
            newCellArray[newStartH + i][newStartW + j] = (*firstArray)[startH + i][startW + j];
        }
    }

    (*firstArray) = newCellArray;
    (*secondArray).clear();

    for (int i = 0; i < this->gridSizeH; i++) {
        (*secondArray).push_back(std::vector<bool>(this->gridSizeW, false));
    }
}