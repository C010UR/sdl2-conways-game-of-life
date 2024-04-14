#include "SDL2_gfxPrimitives.h"
#include "core/app.h"
#include "core/config.h"

#include <sstream>

void App::render()
{
    if (SDL_RenderClear(this->gRenderer) < 0) {
        this->logger->log("App::render", SDL_GetError(), Logger::LogLevel::ERROR);
        return;
    }

    this->renderCellGrid(this->currentCellArray ? &this->cells : &this->cells2);
    this->renderNavBar();

    SDL_SetRenderDrawColor(
        this->gRenderer,
        Config::backgroundColor.r,
        Config::backgroundColor.g,
        Config::backgroundColor.b,
        Config::backgroundColor.a);

    SDL_RenderPresent(this->gRenderer);
}

void App::renderCell(int x, int y, bool isAlive)
{
    if (isAlive) {
        this->aaFilledRectangleColor(
            this->gridStartX + x * this->cellSize,
            this->gridStartY + y * this->cellSize,
            this->gridStartX + (x + 1) * this->cellSize,
            this->gridStartY + (y + 1) * this->cellSize,
            (y + x) % 2 ? Config::livingCellColor : Config::livingCellColor2);
    } else {
        SDL_Color color = (y + x) % 2 ? Config::deadCellColor : Config::deadCellColor2;

        boxRGBA(
            this->gRenderer,
            this->gridStartX + x * this->cellSize,
            this->gridStartY + y * this->cellSize,
            this->gridStartX + (x + 1) * this->cellSize,
            this->gridStartY + (y + 1) * this->cellSize,
            color.r,
            color.g,
            color.b,
            color.a);
    }
}

std::pair<int, int>
App::renderText(std::string msg, int x, int y, SDL_Color fg, SDL_Color bg, bool isCenteredX, bool isCenteredY)
{
    SDL_Surface *surface = TTF_RenderText_Shaded(this->font, msg.c_str(), fg, bg);

    if (surface == nullptr) {
        logger->log("App::renderText", SDL_GetError(), Logger::LogLevel::ERROR);
        return {-1, -1};
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->gRenderer, surface);

    if (texture == nullptr) {
        logger->log("App::renderText", SDL_GetError(), Logger::LogLevel::ERROR);
        return {-1, -1};
    }

    int textW = 0;
    int textH = 0;

    SDL_QueryTexture(texture, nullptr, nullptr, &textW, &textH);
    SDL_Rect dstRect = {x, y, textW, textH};

    if (isCenteredX) {
        dstRect.x = x - textW / 2;
    }

    if (isCenteredY) {
        dstRect.y = y - textH / 2;
    }

    if (SDL_RenderCopy(this->gRenderer, texture, nullptr, &dstRect) < 0) {
        logger->log("App::renderText", SDL_GetError(), Logger::LogLevel::ERROR);
        return {-1, -1};
    }

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    return {textW, textH};
}

void App::renderCellGrid(std::vector<std::vector<bool>> *array)
{
    for (unsigned y = 0; y < (*array).size(); y++) {
        for (unsigned x = 0; x < (*array)[y].size(); x++) {
            this->renderCell(x, y, (*array)[y][x]);
        }
    }
}

void App::aaFilledTrigonColor(int x1, int y1, int x2, int y2, int x3, int y3, SDL_Color color)
{
    filledTrigonRGBA(this->gRenderer, x1 + 1, y1 + 1, x2 - 1, y2, x3 + 1, y3 - 1, color.r, color.g, color.b, color.a);
    aatrigonRGBA(this->gRenderer, x1, y1, x2, y2, x3, y3, color.r, color.g, color.b, color.a);
}

void App::aaFilledRectangleColor(int x1, int y1, int x2, int y2, SDL_Color color)
{
    boxRGBA(this->gRenderer, x1 + 1, y1 + 1, x2 - 1, y2 - 1, color.r, color.g, color.b, color.a);

    aalineRGBA(this->gRenderer, x1, y1, x2, y1, color.r, color.g, color.b, color.a); // Top edge
    aalineRGBA(this->gRenderer, x2, y1, x2, y2, color.r, color.g, color.b, color.a); // Right edge
    aalineRGBA(this->gRenderer, x1, y2, x2, y2, color.r, color.g, color.b, color.a); // Bottom edge
    aalineRGBA(this->gRenderer, x1, y1, x1, y2, color.r, color.g, color.b, color.a); // Left edge
}

void App::renderNavBar()
{
    int padding    = 22;
    int pauseWidth = 10;

    if (this->ups == 0) {
        this->aaFilledRectangleColor(
            padding,
            padding,
            padding + pauseWidth,
            Config::navbarHeight - padding,
            Config::fontColor);

        this->aaFilledRectangleColor(
            padding * 2 + pauseWidth,
            padding,
            padding * 2 + pauseWidth * 2,
            Config::navbarHeight - padding,
            Config::fontColor);
    } else {
        this->aaFilledTrigonColor(
            padding,
            padding,
            padding * 2 + pauseWidth * 2,
            Config::navbarHeight / 2,
            padding,
            Config::navbarHeight - padding,
            Config::fontColor);
    }

    int offsetX = padding * 4 + pauseWidth * 2;
    int offsetY = padding / 2;

    int maxTextWidth = 0;

    std::stringstream upsStream;
    std::stringstream livingStream;
    std::stringstream deadStream;
    std::stringstream cellSizeStream;

    upsStream << "Current UPS: " << this->ups;

    auto cellData = this->cellCount();

    livingStream << "Living Cells: " << cellData.first;
    deadStream << "Dead Cells: " << cellData.second;
    cellSizeStream << "Cell Size: " << this->cellSize;

    // a pretty bad way to display text, but there was no time
    auto textData = this->renderText(upsStream.str(), offsetX, offsetY, Config::fontColor, Config::backgroundColor);
    offsetY += textData.second + padding / 4;

    if (maxTextWidth < textData.first) {
        maxTextWidth = textData.first;
    }

    textData = this->renderText(livingStream.str(), offsetX, offsetY, Config::fontColor, Config::backgroundColor);
    offsetY += textData.second + padding / 4;

    if (maxTextWidth < textData.first) {
        maxTextWidth = textData.first;
    }

    textData = this->renderText(deadStream.str(), offsetX, offsetY, Config::fontColor, Config::backgroundColor);
    
    if (maxTextWidth < textData.first) {
        maxTextWidth = textData.first;
    }

    offsetX += maxTextWidth + padding;
    offsetY = padding / 2;

    textData = this->renderText(cellSizeStream.str(), offsetX, offsetY, Config::fontColor, Config::backgroundColor);

    offsetX += textData.first + padding;
    offsetY = padding / 2;

    textData = this->renderText("Controls:", offsetX, offsetY, Config::fontColor, Config::backgroundColor);
    
    offsetX += textData.first + padding;

    textData = this->renderText("P - Pause", offsetX, offsetY, Config::fontColor, Config::backgroundColor);
    offsetY += textData.second + padding / 4;

    textData = this->renderText("R - Restart", offsetX, offsetY, Config::fontColor, Config::backgroundColor);
    offsetY += textData.second + padding / 4;
    
    textData = this->renderText("ESC - Exit", offsetX, offsetY, Config::fontColor, Config::backgroundColor);
    
    offsetX += textData.first + padding;
    offsetY = padding / 2;

    textData = this->renderText("J - Slow down", offsetX, offsetY, Config::fontColor, Config::backgroundColor);
    offsetY += textData.second + padding / 4;

    textData = this->renderText("K - Speed up", offsetX, offsetY, Config::fontColor, Config::backgroundColor);
    offsetY += textData.second + padding / 4;

    textData = this->renderText("L (during pause) - Make Step", offsetX, offsetY, Config::fontColor, Config::backgroundColor);
    
    offsetX += textData.first + padding;
    offsetY = padding / 2;

    textData = this->renderText("LMB (during pause) - Create a cell", offsetX, offsetY, Config::fontColor, Config::backgroundColor);
    offsetY += textData.second + padding / 4;

    textData = this->renderText("RMB (during pause) - Unalive a cell", offsetX, offsetY, Config::fontColor, Config::backgroundColor);
    
    offsetX += textData.first + padding;
    offsetY = padding / 2;

    textData = this->renderText("I - Make cells smaller", offsetX, offsetY, Config::fontColor, Config::backgroundColor);
    offsetY += textData.second + padding / 4;

    textData = this->renderText("O - Make cells bigger", offsetX, offsetY, Config::fontColor, Config::backgroundColor);
}