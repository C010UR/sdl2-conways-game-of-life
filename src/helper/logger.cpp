#include "helper/logger.h"

#include <iomanip>
#include <sstream>

Logger::Logger(bool isDebug)
{
    this->isDebug = isDebug;
}

void Logger::log(std::string method, std::string message, Logger::LogLevel logLevel)
{
    if (!this->isDebug && (logLevel == Logger::LogLevel::DEBUG || logLevel == Logger::LogLevel::WARNING)) {
        return;
    }

    int colorCode = 0;

    switch (logLevel) {
        case Logger::LogLevel::WARNING:
            colorCode = 33;
            break;
        case Logger::LogLevel::ERROR:
            colorCode = 31;
            break;
        case Logger::LogLevel::INFO:
            colorCode = 36;
            break;
        default:
            colorCode = 0;
            break;
    }

    std::time_t t   = std::time(0);
    std::tm    *now = std::localtime(&t);

    printf(
        "\033[%dm[%04d-%02d-%02d %02d:%02d:%02d]\033[0m \033[33m[%s]\033[0m %s\n",
        colorCode,
        now->tm_year + 1900,
        now->tm_mon + 1,
        now->tm_mday,
        now->tm_hour,
        now->tm_min,
        now->tm_sec,
        method.c_str(),
        message.c_str());
}

void Logger::logMovement(int x, int y, int targetX, int targetY)
{
    std::stringstream strStream;

    strStream << "Moving from (" << x << "; " << y << ") to (" << targetX << ", " << targetY << ")";

    this->log("Logger::logMovement", strStream.str(), Logger::LogLevel::INFO);
}