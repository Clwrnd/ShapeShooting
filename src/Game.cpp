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

    if (player->cInput->up)
    {
        player -> cTransform ->pos.y += player ->cTransform ->speed.y;
    }
    
}

void Game::sUserInput()
{
    sf::Event event;

    while (window.pollEvent(event))
    {

        if (event.type == sf::Event::Closed)
        {
            running = false;
        };

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                spwanBullet(player,Vec2{event.mouseButton.x,event.mouseButton.y});
            }
        }

        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Z:
                player ->cInput ->up = true;
                break;
            
            default:
                break;
            }

        }

          if (event.type == sf::Event::KeyReleased)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Z:
                player ->cInput ->up = false;
                break;
            
            default:
                break;
            }

        }

    }
}

void Game::sLifespan()
{
}

void Game::sRender()
{
    window.clear();

    for (auto e : Mentities.getEntities())
    {
        e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);
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
    e->cInput = std::make_shared<CInput>();
    e->cShape = std::make_shared<CShape>(50, 3, sf::Color::Blue, sf::Color::Green, 7);
    Vec2 pos{400, 400};
    Vec2 spe{3, 3};
    e->cTransform = std::make_shared<CTransform>(pos, spe, 2);
    player = e;
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
    auto e = Mentities.addEntity("bullet");
    e->cShape = std::make_shared<CShape>(5,1000, sf::Color::Red, sf::Color::Red, 1);
    Vec2 pos{mousePos.x, mousePos.y};
    Vec2 spe{0, 0};
    e->cTransform = std::make_shared<CTransform>(pos, spe, 2);
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