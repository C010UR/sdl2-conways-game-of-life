#pragma once

#include <string>
#include <ctime>
#include <iostream>

class Logger
{
  private:
    bool isDebug;

  public:
    enum LogLevel
    {
        DEBUG,
        WARNING,
        ERROR,
        INFO
    };

    Logger(bool isDebug);

    void log(std::string method, std::string message, LogLevel logLevel);
    void logMovement(int x, int y, int targetX, int targetY);
};