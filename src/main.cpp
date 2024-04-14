#include "core/app.h"

int main(int argv, char** args)
{
    Logger logger(true);
    App    app(&logger);

    return app.run();
}