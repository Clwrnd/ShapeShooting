#include "Game.h"
#include <cmath>
#include <iostream>
#include <fstream>

void Game::init(const std::string &config)
{
    std::ifstream configFile;
    configFile.open(config);
    std::string temp, fontPath;
    int w, h, fr, fscr, Rfont, Gfont, Bfont, fs;

    // Read file
    configFile >> temp >> w >> h >> fr >> fscr >> temp >> fontPath >> fs >> Rfont >> Gfont >> Bfont;

    if (fscr)
    {
        window.create(sf::VideoMode({w, h}), "Assignement 2", sf::Style::Fullscreen);
    }
    else
    {
        window.create(sf::VideoMode({w, h}), "Assignement 2");
    }
    window.setFramerateLimit(fr);

    font.loadFromFile(fontPath);

    score_text.setFont(font);
    score_text.setString(std::to_string(score));
    score_text.setPosition({10, 0});
    score_text.setCharacterSize(fs);
    score_text.setColor(sf::Color(Rfont, Gfont, Bfont));

    configFile >> temp >> player_config.SR >> player_config.CR >> player_config.S >>
        player_config.FR >> player_config.FG >> player_config.FB >> player_config.OR >> player_config.OG >> player_config.OB >> player_config.OT >> player_config.V >> player_config.MR>> player_config.MG>> player_config.MB
        >> player_config.MOR>> player_config.MOG>> player_config.MOB;

    configFile >> temp >> ennemy_config.SR >> ennemy_config.CR >> ennemy_config.SMIN >> ennemy_config.SMAX >> ennemy_config.OR >> ennemy_config.OG >> ennemy_config.OB >> ennemy_config.VMIN >> ennemy_config.VMAX >>
        ennemy_config.OT >> ennemy_config.L >> ennemy_config.SI;

    configFile >> temp >> bullet_config.SR >> bullet_config.CR >> bullet_config.S >> bullet_config.FR >> bullet_config.FG >> bullet_config.FB >> bullet_config.OR >> bullet_config.OG >> bullet_config.OB >>
        bullet_config.OT >> bullet_config.V >> bullet_config.L;

    configFile.close();
}

void Game::setPaused()
{
    paused = !paused;
}

void Game::sMovement()
{
    for (auto entity : Mentities.getEntities())
    {
        if (entity->getTag() != "player")
        {
            if (entity->getTag() == "bullet")
            {
                entity->cShape->circle.setFillColor(sf::Color(bullet_config.FR, bullet_config.FG, bullet_config.FB, (static_cast<float>(entity->cLifespan->remaining) / entity->cLifespan->total) * 255));
                entity->cShape->circle.setOutlineColor(sf::Color(bullet_config.OR, bullet_config.OG, bullet_config.OB, (static_cast<float>(entity->cLifespan->remaining) / entity->cLifespan->total) * 255));
            }
            if (entity->getTag() == "smallEnnemy")
            {
                entity->cShape->circle.setFillColor( entity->cShape->circle.getFillColor() -  sf::Color(0,0,0,entity->cShape->circle.getFillColor().a) + sf::Color(0,0,0,(static_cast<float>(entity->cLifespan->remaining) / entity->cLifespan->total) * 255) ) ;
                entity->cShape->circle.setOutlineColor( entity->cShape->circle.getOutlineColor() -  sf::Color(0,0,0,entity->cShape->circle.getOutlineColor().a) + sf::Color(0,0,0,(static_cast<float>(entity->cLifespan->remaining) / entity->cLifespan->total) * 255) ) ;
            }
            if (entity->getTag() == "mvPlayer")
            {
                entity->cShape->circle.setFillColor(sf::Color(player_config.MR, player_config.MG, player_config.MB, (static_cast<float>(entity->cLifespan->remaining) / entity->cLifespan->total) * 255));
            }
            if(entity->getTag()=="spW")
            {
               if(entity->cDelayedeffect->final_effect==(entity->cLifespan->total-entity->cLifespan->remaining))
               {
                 entity->cTransform->speed*=0; 
                 auto wave = Mentities.addEntity("wave");
                 wave->cShape = std::make_shared<CShape>(0, 100,sf::Color::Transparent,sf::Color::Magenta,1);
                 wave->cTransform = std::make_shared<CTransform>(entity->cTransform->pos,
                                                          Vec2{0, 0}, 0);
                 wave->cWave = std::make_shared<CWave>(200);
               } 
               else if (entity->cDelayedeffect->final_effect>(entity->cLifespan->total-entity->cLifespan->remaining))
               {
                entity->cShape->circle.setFillColor(entity->cShape->circle.getFillColor()+sf::Color(2,0,0,0));
               } 
               else
               {
                entity->cShape->circle.setFillColor(entity->cShape->circle.getFillColor()-sf::Color(0,0,0,3));
                entity->cShape->circle.setOutlineColor(entity->cShape->circle.getFillColor()-sf::Color(0,0,0,3));
               } 
            }
            if(entity->getTag()=="wave")
            {
                entity->cShape->circle.setRadius(entity->cShape->circle.getRadius()+3);
                entity->cShape->circle.setOrigin(entity->cShape->circle.getRadius(), entity->cShape->circle.getRadius());

            }
            if (entity->getTag() == "ennemy" || entity->getTag() == "smallEnnemy")
            {
                if (entity->cShape->circle.getGlobalBounds().left + entity->cTransform->speed.x < 0)
                {
                    entity->cTransform->speed.x = -entity->cTransform->speed.x;
                }
                if (entity->cShape->circle.getGlobalBounds().left + entity->cShape->circle.getGlobalBounds().width + entity->cTransform->speed.x > window.getSize().x)
                {
                    entity->cTransform->speed.x = -entity->cTransform->speed.x;
                }
                if (entity->cShape->circle.getGlobalBounds().top + entity->cTransform->speed.y < 0)
                {
                    entity->cTransform->speed.y = -entity->cTransform->speed.y;
                }
                if (entity->cShape->circle.getGlobalBounds().top + entity->cShape->circle.getGlobalBounds().height + entity->cTransform->speed.x > window.getSize().y)
                {
                    entity->cTransform->speed.y = -entity->cTransform->speed.y;
                }
            }
            entity->cTransform->pos.x += entity->cTransform->speed.x;
            entity->cTransform->pos.y += entity->cTransform->speed.y;
        }
    }

    // Player Movements
    float shapeBorder = player->cShape->circle.getRadius() + player->cShape->circle.getOutlineThickness();

    if ((player->cInput->up || player->cInput->down) && (player->cInput->left || player->cInput->right))
    {
        player->cTransform->speed *= (std::sqrt(2) / 2);
    }

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

    if ((player->cInput->up || player->cInput->down) && (player->cInput->left || player->cInput->right))
    {
        player->cTransform->speed /= (std::sqrt(2) / 2);
    }

    if (player->cInput->down || player->cInput->up || player->cInput->right || player->cInput->left)
    {
        auto effect = Mentities.addEntity("mvPlayer");
        effect->cShape = std::make_shared<CShape>(7, 10, sf::Color(player_config.MR, player_config.MG, player_config.MB), sf::Color(player_config.MOR, player_config.MOG, player_config.MOB), 1);
        effect->cTransform = std::make_shared<CTransform>(Vec2{player->cTransform->pos.x,
                                                               player->cTransform->pos.y},
                                                          Vec2{0, 0}, 20);
        effect->cLifespan = std::make_shared<CLifespan>(20, 20);
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
            if(event.mouseButton.button == sf::Mouse::Right)
            {
                spwanSpecWeapon(player,Vec2{static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)});
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
        if (e->getTag() == "bullet" || e->getTag() == "smallEnnemy" || e->getTag() == "mvPlayer"||e->getTag() == "spW")
        {
            e->cLifespan->remaining--;
            if (e->cLifespan->remaining == 0)
            {
                e->destroy();
            }
        }
        if(e->getTag() == "wave")
        {
            if(e->cWave->radius<e->cShape->circle.getRadius())
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
    if (current_frame - lastTimeEnemySpwanded == ennemy_config.SI)
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
            if (bullet->cTransform->pos.dist(ennemy->cTransform->pos) < bullet_config.CR+ennemy_config.CR)
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
            if (bullet->cTransform->pos.dist(ennemy->cTransform->pos) < bullet_config.CR+ennemy_config.CR)
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
        if (player->cTransform->pos.dist(ennemy->cTransform->pos) < player_config.CR+ennemy_config.CR)
        {
            spawnSmallEnemies(ennemy);
            ennemy->destroy();
            player->cTransform->pos.x = window.getSize().x / 2;
            player->cTransform->pos.y = window.getSize().y / 2;
            score=0;
            score_text.setString(std::to_string(score));
        }
    }

    for (auto ennemy : Mentities.getEntities("smallEnnemy"))
    {
        if (player->cTransform->pos.dist(ennemy->cTransform->pos) <  player_config.CR+ennemy_config.CR)
        {
            ennemy->destroy();
            player->cTransform->pos.x = window.getSize().x / 2;
            player->cTransform->pos.y = window.getSize().y / 2;
            score=0;
            score_text.setString(std::to_string(score));
        }
    }

    for(auto wave : Mentities.getEntities("wave"))
    {
        for(auto ennemy:Mentities.getEntities("ennemy"))
        {
            if(wave->cTransform->pos.dist(ennemy->cTransform->pos)<wave->cShape->circle.getRadius()+ennemy_config.CR)
            {
                spawnSmallEnemies(ennemy);
                ennemy->destroy();
                score += ennemy->cScore->score;
                score_text.setString(std::to_string(score));
            }
        }
        
        for(auto ennemy:Mentities.getEntities("smallEnnemy"))
        {
            if(wave->cTransform->pos.dist(ennemy->cTransform->pos)<wave->cShape->circle.getRadius()+ennemy_config.CR)
            {
                ennemy->destroy();
                score += ennemy->cScore->score;
                score_text.setString(std::to_string(score));
            }
        }
    }
}

void Game::spawnPlayer()
{
    auto e = Mentities.addEntity("player");
    e->cInput = std::make_shared<CInput>();
    e->cShape = std::make_shared<CShape>(player_config.SR, player_config.V, sf::Color(player_config.FR, player_config.FG, player_config.FB),
                                         sf::Color(player_config.OR, player_config.OG, player_config.OB), player_config.OT);
    e->cTransform = std::make_shared<CTransform>(Vec2{static_cast<float>(window.getSize().x / 2), static_cast<float>(window.getSize().y / 2)}, Vec2{player_config.S, player_config.S}, 2);
    player = e;
}

void Game::spawnEnemy()
{
    auto ennemy = Mentities.addEntity("ennemy");
    ennemy->cShape = std::make_shared<CShape>(ennemy_config.SR, rand() % (ennemy_config.VMAX - ennemy_config.VMIN + 1) + ennemy_config.VMIN,
                                              sf::Color(rand() % 256, rand() % 256, rand() % 256), sf::Color(ennemy_config.OR, ennemy_config.OG, ennemy_config.OB), ennemy_config.OT);
    int borderY = ennemy->cShape->circle.getRadius()+ ennemy->cShape->circle.getOutlineThickness() ;
    int borderX = ennemy->cShape->circle.getLocalBounds().width;
    ennemy->cTransform = std::make_shared<CTransform>(Vec2{static_cast<float>(rand() % (window.getSize().x - 2*borderY) + borderY), static_cast<float>(rand() % (window.getSize().y - 2*borderY) + borderY)},
                                                      Vec2{static_cast<float>(std::pow(-1, (rand() % 2)) * (rand() % (ennemy_config.SMAX -
                                                                                                                      ennemy_config.SMIN + 1) +
                                                                                                            ennemy_config.SMIN)),
                                                           static_cast<float>(std::pow(-1, (rand() % 2)) * (rand() % (ennemy_config.SMAX -
                                                                                                                      ennemy_config.SMIN + 1) +
                                                                                                            ennemy_config.SMIN))},
                                                      2);
    ennemy->cScore = std::make_shared<CScore>(100 * ennemy->cShape->circle.getPointCount());
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> entity)
{
    int nPoint = entity->cShape->circle.getPointCount();
    for (size_t i = 1; i <= nPoint; i++)
    {
        auto smallE = Mentities.addEntity("smallEnnemy");
        smallE->cShape = std::make_shared<CShape>(18, entity->cShape->circle.getPointCount(), entity->cShape->circle.getFillColor(), entity->cShape->circle.getOutlineColor(), 3);

        smallE->cTransform = std::make_shared<CTransform>(Vec2{entity->cTransform->pos.x, entity->cTransform->pos.y}, Vec2{static_cast<float>( std::cos(2 * M_PI / entity->cShape->circle.getPointCount() * i)), static_cast<float>( std::sin(2 * M_PI / entity->cShape->circle.getPointCount() * i))}, 2);
        smallE->cLifespan = std::make_shared<CLifespan>(ennemy_config.L, ennemy_config.L);
        smallE->cScore = std::make_shared<CScore>(2 * entity->cScore->score);
    }
}

void Game::spwanSpecWeapon(std::shared_ptr<Entity> entity,const Vec2 & mousePos)
{
    if (current_frame-lastTimeSpecSpwanded > 120)
    {
        auto spW = Mentities.addEntity("spW");
        spW->cShape=std::make_shared<CShape>(15,100,sf::Color::Black,sf::Color::Red,3);
        float angle = std::atan2(mousePos.y - player->cTransform->pos.y, mousePos.x - player->cTransform->pos.x);

        Vec2 spe{ 2*std::cos(angle), 2*std::sin(angle)};
        spW->cTransform = std::make_shared<CTransform>(player->cTransform->pos, spe , 2);
        spW->cLifespan= std::make_shared<CLifespan>(240,240);
        spW->cDelayedeffect = std::make_shared<CDelayedeffect>(125);

        lastTimeSpecSpwanded= current_frame;
    }
    
}

void Game::spwanBullet(std::shared_ptr<Entity> player, const Vec2 &mousePos)
{
    auto e = Mentities.addEntity("bullet");
    e->cShape = std::make_shared<CShape>(bullet_config.SR, bullet_config.V, sf::Color(bullet_config.FR, bullet_config.FG, bullet_config.FB), sf::Color(bullet_config.OR, bullet_config.OG, bullet_config.OB), bullet_config.OT);
    Vec2 pos{player->cTransform->pos.x, player->cTransform->pos.y};

    float angle = std::atan2(mousePos.y - player->cTransform->pos.y, mousePos.x - player->cTransform->pos.x);

    Vec2 spe{bullet_config.S * std::cos(angle), bullet_config.S * std::sin(angle)};
    e->cTransform = std::make_shared<CTransform>(pos, spe, 2);
    e->cLifespan = std::make_shared<CLifespan>(bullet_config.L, bullet_config.L);
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
        if (!paused)
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
        else
        {
            sUserInput();
            sRender();
        }
    }
}