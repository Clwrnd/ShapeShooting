#include "Game.h"

int main()
{
    std::string config("config.txt");
    Game g(config);
    g.run();
}
