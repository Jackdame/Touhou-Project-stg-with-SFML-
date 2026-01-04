#include "Game.h"
#include <ctime>
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) // ¹Ø±Õ¿ØÖÆÌ¨
int main() {
    srand(static_cast<unsigned>(time(0)));
    Game game;
    game.run();
    return 0;
}