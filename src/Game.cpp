#include "Game.h"
#include <cmath>
#include <iostream>

void Game::init(const std::string &config)
{
    window.create(sf::VideoMode({1480, 1000}), "Assignement 2");
    window.setFramerateLimit(60);

    font.loadFromFile("C:/Users/cidmo/Documents/CS_PROJECT/LearnCpp/A2/Assignement_2/src/youngtechs.ttf"); 
    score_text.setFont(font);
    score_text.setString(std::to_string (score) );
    score_text.setPosition({0,0});
}

void Game::setPaused()
{
    paused= !paused;
}

void Game::sMovement()
{
    for (auto entity : Mentities.getEntities())
    {
        if (entity->getTag() != "player")
        {
            if (entity->getTag() == "bullet")
            {
                entity->cShape->circle.setFillColor(sf::Color(23, 123, 12, (static_cast<float>(entity->cLifespan->remaining) / entity->cLifespan->total) * 255));
                entity->cShape->circle.setOutlineColor(sf::Color(23, 123, 12, (static_cast<float>(entity->cLifespan->remaining) / entity->cLifespan->total) * 255));
            }
            if(entity->getTag() == "smallEnnemy")
            {
               entity->cShape->circle.setFillColor(sf::Color(255,255, 255, (static_cast<float>(entity->cLifespan->remaining) / entity->cLifespan->total) * 255));
               entity->cShape->circle.setOutlineColor(sf::Color(255,255, 0, (static_cast<float>(entity->cLifespan->remaining) / entity->cLifespan->total) * 255));
            }
            if(entity->getTag() == "mvPlayer")
            {
               entity->cShape->circle.setFillColor(sf::Color(0,255,0,(static_cast<float>(entity->cLifespan->remaining) / entity->cLifespan->total) * 255));
            }
            if (entity->getTag() == "ennemy" || entity->getTag() =="smallEnnemy")
            {
                if (entity->cShape->circle.getGlobalBounds().left + entity->cTransform->speed.x < 0)
                {
                    entity->cTransform->speed.x= -entity->cTransform->speed.x;
                }
                if (entity->cShape->circle.getGlobalBounds().left + entity->cShape->circle.getGlobalBounds().width + entity->cTransform->speed.x  > window.getSize().x)
                {
                    entity->cTransform->speed.x=-entity->cTransform->speed.x;
                }
                if (entity->cShape->circle.getGlobalBounds().top + entity->cTransform->speed.y  < 0)
                {
                    entity->cTransform->speed.y=-entity->cTransform->speed.y;
                }
                if (entity->cShape->circle.getGlobalBounds().top + entity->cShape->circle.getGlobalBounds().height + entity->cTransform->speed.x  > window.getSize().y)
                {
                    entity->cTransform->speed.y=-entity->cTransform->speed.y;
                }
            }
            entity->cTransform->pos.x += entity->cTransform->speed.x;
            entity->cTransform->pos.y += entity->cTransform->speed.y;
        }
    }

    // Player Movements
    float shapeBorder = player->cShape->circle.getRadius() + player->cShape->circle.getOutlineThickness();

    if (player->cInput->up && player->cTransform->pos.y - player->cTransform->speed.y - shapeBorder > 0)
    {        
        player->cTransform->pos.y -= player->cTransform->speed.y;
    }

    if (player->cInput->left && player->cTransform->pos.x - player->cTransform->speed.x - shapeBorder > 0)
    {
        player->cTransform->pos.x -= player->cTransform->speed.x;
    }

    if (player->cInput->right && player->cTransform->pos.x + player->cTransform->speed.x + shapeBorder < window.getSize().x)
    {
        player->cTransform->pos.x += player->cTransform->speed.x;
    }

    if (player->cInput->down && player->cTransform->pos.y + player->cTransform->speed.y + shapeBorder < window.getSize().y)
    {
        player->cTransform->pos.y += player->cTransform->speed.y;
    }

    if(player->cInput->down || player->cInput->up || player->cInput->right || player->cInput->left)
    {
           auto effect = Mentities.addEntity("mvPlayer");
           effect->cShape=std::make_shared<CShape>(7,10, sf::Color::Blue,sf::Color::White, 0);
           effect->cTransform = std::make_shared<CTransform>(Vec2{player->cTransform->pos.x,
            player->cTransform->pos.y},Vec2{0,0},10);
        effect->cLifespan=std::make_shared<CLifespan>(20,20);    
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
            case sf::Keyboard::P:
                setPaused();
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
    for (auto e : Mentities.getEntities())
    {
        if(e->getTag()=="bullet" || e->getTag()=="smallEnnemy" || e->getTag()=="mvPlayer")
        {
        e->cLifespan->remaining--;
        if (e->cLifespan->remaining == 0)
        {
            e->destroy();
        }
        }
    } 
}

void Game::sRender()
{
    window.clear();

    for (auto e : Mentities.getEntities())
    {
        e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);
        e->cShape->circle.rotate(e->cTransform->ang);
        window.draw(e->cShape->circle);
    }
    window.draw(score_text);

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
    for (auto bullet : Mentities.getEntities("bullet"))
    {
        for (auto ennemy : Mentities.getEntities("ennemy"))
        {
            if (bullet->cTransform->pos.dist(ennemy->cTransform->pos)<43)
            {
                spawnSmallEnemies(ennemy);
                bullet->destroy();
                ennemy->destroy();
                score += ennemy->cScore->score;
                score_text.setString(std::to_string(score));            
            }
           
        }

        for (auto ennemy : Mentities.getEntities("smallEnnemy"))
        {
            if (bullet->cTransform->pos.dist(ennemy->cTransform->pos)<25)
            {
                bullet->destroy();
                ennemy->destroy();
                score += ennemy->cScore->score;
                score_text.setString(std::to_string(score));    
            }
            
        }
    }

    for (auto ennemy : Mentities.getEntities("ennemy"))
    {
        if (player->cTransform->pos.dist(ennemy->cTransform->pos) < 65)
        {
            spawnSmallEnemies(ennemy);
            ennemy->destroy();
            player->cTransform->pos.x = window.getSize().x / 2;
            player->cTransform->pos.y = window.getSize().y / 2;
        }
    }

    for (auto ennemy : Mentities.getEntities("smallEnnemy"))
    {
        if (player->cTransform->pos.dist(ennemy->cTransform->pos) < 65)
        {
            ennemy->destroy();
            player->cTransform->pos.x = window.getSize().x / 2;
            player->cTransform->pos.y = window.getSize().y / 2;
        }
    }

}


void Game::spawnPlayer()
{
    auto e = Mentities.addEntity("player");
    e->cInput = std::make_shared<CInput>();
    e->cShape = std::make_shared<CShape>(40, 5, sf::Color::Blue, sf::Color::Green, 7);
    e->cTransform = std::make_shared<CTransform>(Vec2{static_cast<float>(window.getSize().x / 2), static_cast<float>(window.getSize().y / 2)}, Vec2{3, 3}, 2);
    player = e;
}

void Game::spawnEnemy()
{
    auto ennemy = Mentities.addEntity("ennemy");
    ennemy->cShape = std::make_shared<CShape>(20, 6, sf::Color::White, sf::Color::Yellow, 3);
    ennemy->cTransform = std::make_shared<CTransform>(Vec2{static_cast<float>(rand() % 800 + 30), static_cast<float>(
                                                                                                      rand() % 800 + 70)},
                                                      Vec2{static_cast<float>(std::pow(-1, (rand() % 2)) * (rand() % 6 +3)),
                                                           static_cast<float>(std::pow(-1, static_cast<double>(rand() % 2 +3    )) * (rand() % 6))},
                                                      2);
    ennemy->cScore=std::make_shared<CScore>(100*ennemy->cShape->circle.getPointCount());
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> entity)
{
    int nPoint =entity->cShape->circle.getPointCount();
    for (size_t i = 1; i <=nPoint ; i++)
    {
        auto smallE = Mentities.addEntity("smallEnnemy");
        smallE->cShape = std::make_shared<CShape>(7,6,sf::Color::White, sf::Color::Yellow, 3); 
        
        smallE->cTransform = std::make_shared<CTransform>(Vec2{entity->cTransform->pos.x,entity->cTransform->pos.y}
                ,Vec2{ static_cast<float> ( 5*std::cos(2*M_PI/6*i) ) , static_cast<float> (
                    5*std::sin(2*M_PI/6*i) )},2);
        smallE->cLifespan = std::make_shared<CLifespan>(100,100);
        smallE->cScore = std::make_shared<CScore>(2*entity->cScore->score);
    }
    
}

void Game::spwanSpecWeapon(std::shared_ptr<Entity> entity)
{
}

void Game::spwanBullet(std::shared_ptr<Entity> player, const Vec2 &mousePos)
{
    auto e = Mentities.addEntity("bullet");
    e->cShape = std::make_shared<CShape>(15, 7, sf::Color::Red, sf::Color::Red, 0);
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
        if(!paused)
        {
        Mentities.update();
        sEnemySpawner();
        sMovement();
        sCollision();
        sUserInput();
        sRender();
        sLifespan();
        current_frame++;
        } else
        {
            sUserInput();
            sRender();
        }

    }
}