#include <ctime>
#include <cstdlib>
#include<string>

#include "Game.h"


sf::Clock timer;
float deltaTime;        //This will represent the global deltaTime variable

int main()
{
    Game game;

    while (game.isGameRunning()) {      //As long as the game is running, the game will update and render
        game.Update();
        game.Render();
        deltaTime = timer.restart().asSeconds();    //The deltaTime will count. Once the frame is over, it will reset, resulting in the time between the last frame and the current one
    }

    return 0;
}