#include "Game.h"


Game::Game(){
 //   
}
void Game::run(){
Game::window.create(sf::VideoMode({1000,1000}),"test");
while (Game::window.isOpen())
{
    for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
}

}