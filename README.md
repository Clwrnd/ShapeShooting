# Specifications

## Features:

### Player:
1. The player is represented by a shape which is defined in the config file
2. The player must spwan in the center of the screen at the beginning of the game, and after it dies (collides with enemy)
3. The player moves by a speed read from the config file in these directions: \
Up -> "Z" key, Left-> "Q" key, Right-> "D" and Down-> "S" key.
4. The player is confined to move only within the bounds of the window
5. The player will shoot a bullet toward the mouse pointer when the left mouse button is clicked. The speeed, size and lipespan of the bullets are read from the config file.

### Special Ability:
You are free to come up with your own 'special move' which is fired by the player when the right mouse button is clicked. This special  ability must: 
1. Multiple entities (bullets etc) spawned by special weapon
2. Entities have some unique graphic associate with them
3. A unique game mechanic is introduced via a new component
4. A 'cooldown timer' must be implemented for the special weapon
The properties of the special move are not in the config file.
 
### Enemy (s): 
1. Ennemies will spawn in a random location on the screen every X frames, where X is defined in the configuration file. 
2. Enemies must not overlap the sides of the screen at the time of spawn.
3. Ennemies shapes have random number of vertices, between a given minimum and maximum number, which is specified in the config file.
4. Enemy shape radius will be specified in the config file.
5. Enemies will be given a random color upon spwaning.
6. Enemies will be given a random speed upon spwaning, between a minimum and maximum number, which is specified in the configuration file.
7. When an enemy reaches the edge of the window, it should bounce off in the opposite direction at the same speed.
When (large) enemies collide with a bullet or player, they are destroyed, and N small enemies spawn in its placen where N is the nulber of vertices o the original enemy. These small entities travel outward at angles at a fixed intervals equal to (360/vertices).

### Score:
1. Each time an enmy spawns, it is given a score component of N*100, where N is the nulber of vertices it has. Small ennemies get double this value.
2. If a player bullet kills an enemy, the game score is increased by th score component of the enemy killed.
3. The score should be displayed with the font specidied by the config file in the top-left corner of the screen.

### Drawing:

1. In the render system, all entities should be given a slow rotation, which makes the game look a little nicer.
2. Any other effects that do not affect the gameplay can be added.
3. Any Entity with a lifespan is currently alive, it should have its Color alpha channel set to a ratio depending on how long it has left to live. 

## Configuration File:

1. Window: **"W"** idht, **"H"** eight, **"F"** rame_limit, **"F"** ull-screen. 

2. Font: **"F"** ont, **"S"** ize, R, G, B.

3. Player: **SR** (Shape radius: int), **CR** (Collision Radius: int), **S**peed (float), **FR-FG-FB** (Fill color: int), **OR-OG-OB** (Outline color: int), **OT** (Outline Thickness: int), **V** (Shape Vertices: int)

4. Enemy: **SR**, **CR**, **SMIN**, **SMAX** (Min max speed float), **OR-OG-OB**,**OT**, **VMIN**,**VMAX** (min max vertices: int),
**L** (small lifespan: int), **SI** (Spawn Intervalle)

5. Bullet **SR**, **CR**, **S**, **FR-FG-FB**, **OR-OG-OB**,**OT**, **V**,**L**

## Hints:
 1. Implement Vec2 class
 2. Implement basic fonctionality in the EntityManager class. \
 Implement the EntityManager's "addEntity()" and "update()"
 3. SpawnPlayer(), Game::sRender(),spawnEnemy(),spawnBullet()
 4. Player movement
 5. Deletes dead entities
 6. getEntities(tag)
 7. Collision, destroy() for dead entities
 
From **COMP 4300, Memorial University, CANADA** teached by **Associate Professor Dave Churchill**. \
Source: https://www.youtube.com/watch?v=OmzU_-zbE7o&t=3675s

An entire majority of the game's settings are adjustable via the config.txt file (you should change the path to it in the main.cpp), excecpt for the special Weapon that can
uniquely me modified directly in the game.cpp file in the same name fonctions. 

Large improvments and additions could be made to this project but as a training project and not a genuine long term project, it is for me largely satisfactory in this current state ! :)
