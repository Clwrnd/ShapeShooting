#include "Game.h"
#include <cmath>
#include <iostream>

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
    for (auto entity : Mentities.getEntities())
    {
        if (entity->getTag() != "player")
        {
            entity->cTransform->pos.x += entity->cTransform->speed.x;
            entity->cTransform->pos.y += entity->cTransform->speed.y;
            if (entity->getTag() == "bullet")
            {
        entity ->cShape ->circle.setFillColor(sf::Color(23,123,12,(static_cast<float>(entity->cLifespan->remaining)/
        entity->cLifespan->total)*255
        ));
            }
        }
    }

    // Player Movements

    if (player->cInput->up)
    {
        player->cTransform->pos.y -= player->cTransform->speed.y;
    }

    if (player->cInput->left)
    {
        player->cTransform->pos.x -= player->cTransform->speed.x;
    }

    if (player->cInput->right)
    {
        player->cTransform->pos.x += player->cTransform->speed.x;
    }

    if (player->cInput->down)
    {
        player->cTransform->pos.y += player->cTransform->speed.y;
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
                spwanBullet(player, Vec2{static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)});
            }
        }

        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Z:
                player->cInput->up = true;
                break;
            case sf::Keyboard::Q:
                player->cInput->left = true;
                break;
            case sf::Keyboard::S:
                player->cInput->down = true;
                break;
            case sf::Keyboard::D:
                player->cInput->right = true;
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
                player->cInput->up = false;
                break;
            case sf::Keyboard::Q:
                player->cInput->left = false;
                break;
            case sf::Keyboard::S:
                player->cInput->down = false;
                break;
            case sf::Keyboard::D:
                player->cInput->right = false;
                break;

            default:
                break;
            }
        }
    }
}

void Game::sLifespan()
{
    for (auto e : Mentities.getEntities("bullet"))
    {
        e->cLifespan->remaining--;
        if (e->cLifespan->remaining == 0)
        {
            e->destroy();
        }
    }
}

void Game::sRender()
{
    window.clear();

    for (auto e : Mentities.getEntities())
    {
        if (e->isActive())
        {
            e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);
            window.draw(e->cShape->circle);
        }
    }

    window.display();
}

void Game::sEnemySpawner()
{
    if (current_frame - lastTimeEnemySpwanded == 120)
    {
        spawnEnemy();
        lastTimeEnemySpwanded = current_frame;
    }
}

void Game::sCollision()
{
}

void Game::spawnPlayer()
{
    auto e = Mentities.addEntity("player");
    e->cInput = std::make_shared<CInput>();
    e->cShape = std::make_shared<CShape>(50, 3, sf::Color::Blue, sf::Color::Green, 7);
    e->cTransform = std::make_shared<CTransform>(Vec2{400, 400}, Vec2{3, 3}, 2);
    player = e;
}

void Game::spawnEnemy()
{
    auto ennemy = Mentities.addEntity("ennemy");
    ennemy->cShape = std::make_shared<CShape>(20, 6, sf::Color::White, sf::Color::Yellow, 3);
    ennemy->cTransform = std::make_shared<CTransform>(Vec2{ static_cast<float> ( rand() % 900 + 30 ),static_cast<float> (
     rand() % 900 + 70 )}, Vec2{3, 3}, 2);
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> entity)
{
}

void Game::spwanSpecWeapon(std::shared_ptr<Entity> entity)
{
}

void Game::spwanBullet(std::shared_ptr<Entity> player, const Vec2 &mousePos)
{
    auto e = Mentities.addEntity("bullet");
    e->cShape = std::make_shared<CShape>(15, 1000, sf::Color::Red, sf::Color::Red, 0);
    Vec2 pos{player->cTransform->pos.x, player->cTransform->pos.y};

    float angle = std::atan2(mousePos.y - player->cTransform->pos.y, mousePos.x - player->cTransform->pos.x);

    Vec2 spe{5 * std::cos(angle), 5 * std::sin(angle)};
    e->cTransform = std::make_shared<CTransform>(pos, spe, 2);
    e->cLifespan = std::make_shared<CLifespan>(100, 100);
}

Game::Game(const std::string &config)
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
        sLifespan();
        current_frame++;
    }
}