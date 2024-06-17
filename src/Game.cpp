#include "Game.h"

void Game::init(const std::string &config)
{
    window.create(sf::VideoMode({1280, 860}), "Assignement 2");
    window.setFramerateLimit(60);
}

void Game::setPaused(bool paused_in)
{
}

void Game::sMovement()
{
}

void Game::sUserInput()
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        
        if (event.type == sf::Event::Closed)
        {
            running = false;
        }
    }
}

void Game::sLifespan()
{
}

void Game::sRender()
{
    window.clear();

    for  (auto e: Mentities.getEntities())
    {
        e->cShape->circle.setPosition(e->cTransform->pos.x,e->cTransform->pos.y);S
        window.draw(e->cShape->circle);
    }

    window.display();
}

void Game::sEnemySpawner()
{
}

void Game::sCollision()
{
}

void Game::spawnPlayer()
{
    auto e = Mentities.addEntity("player");
    e->cShape=std::make_shared<CShape>(10,3,sf::Color::Blue,sf::Color::Green,5);
    Vec2 pos{100,400};
    Vec2 spe{0,0};
    e->cTransform=std::make_shared<CTransform>(pos,spe,2);
}

void Game::spawnEnemy()
{
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> entity)
{
}

void Game::spwanSpecWeapon(std::shared_ptr<Entity> entity)
{
}

void Game::spwanBullet(std::shared_ptr<Entity> Entity, const Vec2 &mousePos)
{
}

Game::Game(std::string &config)
{
    init(config);
}
void Game::run()
{
    spawnPlayer();
    while (running)
    {
        Mentities.update();
        sEnemySpawner();
        sMovement();
        sCollision();
        sUserInput();
        sRender();
        current_frame++;
    }
}