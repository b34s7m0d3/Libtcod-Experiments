#include "main.h"

Engine::Engine(int screenWidth, int screenHeight) : gameStatus(STARTUP), fovRadius(10), screenWidth(screenWidth), screenHeight(screenHeight)
{
    TCODConsole::initRoot(screenWidth, screenHeight, "libtcod C++ tutorial", false);
    gui = new Gui();
}

Engine::~Engine()
{
    actors.clearAndDelete();
    delete map;
    delete gui;
}

void Engine::init()
{
    player = new Actor(screenWidth/2, screenHeight/2, '@', TCODColor::white, "player");
    player->destructible = new PlayerDestructible(30, 2, true, "your cadaver");
    player->attacker = new Attacker(5);
    player->ai = new PlayerAi();
    player->container = new Container(26);
    actors.push(player);
    map = new Map(screenWidth, screenHeight - 7);
    map->init(true);

    gui->message(TCODColor::red, "Welcome stranger!\nPrepare to perish in the Tombs of the Ancient Kings.");
}

void Engine::load()
{
    if(TCODSystem::fileExists("game.sav"))
    {
        TCODZip zip;
        zip.loadFromFile("game.sav");

        // load map
        int width = zip.getInt();
        int height = zip.getInt();
        map = new Map(width, height);
        map->load(zip);
        /*
        // load player
        player = new Actor(0, 0, 0, TCODColor::white, NULL);
        player->load(zip);
        actors.push(player);

        // load actors
        int numOfActors = zip.getInt();
        while(numOfActors > 0)
        {
            Actor *actor = new Actor(0, 0, 0, TCODColor::white, NULL);
            actor->load(zip);
            actors.push(actor);
            numOfActors--;
        }*/

        // load message log
        gui->load(zip);

    }
    else
    {
        init();
    }
}

void Engine::save()
{
    if(player->destructible->isDead())
    {
        TCODSystem::deleteFile("game.sav");
    }
    else
    {
        TCODZip zip;

        // save map
        zip.putInt(map->width);
        zip.putInt(map->height);
        map->save(zip);
        /*
        // save actors
        player->save(zip);
        zip.putInt(actors.size() - 1);
        for(Actor **iterator = actors.begin(); iterator != actors.end(); iterator++)
        {
            if(*iterator != player)
            {
                (*iterator)->save(zip);
            }
        }*/

        // save message log
        gui->save(zip);

        zip.saveToFile("game.sav");
    }
}

bool Engine::update()
{
    if(gameStatus == STARTUP) map->computeFov();
    gameStatus = IDLE;

    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS | TCOD_EVENT_MOUSE, &lastKey, &mouse);
    player->update();

    if(gameStatus == NEW_TURN)
    {
        for(Actor **iterator = actors.begin(); iterator != actors.end(); iterator++)
        {
            Actor *actor = *iterator;
            if(actor != player)
            {
                actor->update();
            }
        }
    }

    return lastKey.vk == TCODK_ESCAPE;
}

void Engine::render()
{
    TCODConsole::root->clear(); // root is a static pointer member of TCODConsole

    // draw the map
    map->render();

    // draw the actors
    for(Actor **iterator=actors.begin(); iterator != actors.end(); iterator++) // **iterator is a pointer to a pointer?
    {
        Actor *actor = *iterator;
        if(map->isInFov(actor->x, actor->y))
        {
            actor->render();
        }
    }

    player->render();
    gui->render();

	// show the player's stats
	TCODConsole::root->print(1, screenHeight-2, "HP : %d/%d", (int)player->destructible->hp, (int)player->destructible->maxHp);
}

void Engine::sendToBack(Actor *actor)
{
    actors.remove(actor);
    actors.insertBefore(actor,0);
}

bool Engine::pickATile(int *x, int *y, float maxRange)
{
    while (!TCODConsole::isWindowClosed())
    {
        render();

        // Highlight available range from player
        for(int cx = 0; cx < map->width; cx++)
        {
            for(int cy = 0; cy < map->height; cy++)
            {
                if(map->isInFov(cx, cy) && (maxRange == 0 || player->getDistance(cx, cy) <= maxRange))
                {
                    TCODColor col = TCODConsole::root->getCharBackground(cx, cy);
                    col = col * 1.2f;

                    TCODConsole::root->setCharBackground(cx, cy, col);
                }
            }
        }

        // Get mouse coordinates or pending keystroke
        TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS | TCOD_EVENT_MOUSE, &lastKey, &mouse);
        if(map->isInFov(mouse.cx, mouse.cy) && (maxRange == 0 || player->getDistance(mouse.cx, mouse.cy) <= maxRange))
        {
            // Highlight mouse coordinates
            TCODConsole::root->setCharBackground(mouse.cx, mouse.cy, TCODColor::white);

            // Set x and y if clicked
            if(mouse.lbutton_pressed)
            {
                *x = mouse.cx;
                *y = mouse.cy;
                return true;
            }
        }

        // Disregard if user cancelled action by right clicking or pressing key
        if(mouse.rbutton_pressed || lastKey.vk != TCODK_NONE)
        {
            return false;
        }

        TCODConsole::flush();
    }

    return false;
}

Actor *Engine::getActor(int x, int y) const
{
    for(Actor **iterator = actors.begin(); iterator != actors.end(); iterator++)
    {
        Actor *actor = *iterator;
        if(actor->x == x && actor->y == y && actor->destructible && !actor->destructible->isDead())
        {
            return actor;
        }
    }

    return NULL;
}

Actor *Engine::getClosestMonster(int x, int y, float range) const
{
    Actor *closestMonster = NULL;
    float closestDistance = -1;

    for(Actor **iterator = actors.begin(); iterator != actors.end(); iterator++)
    {
        Actor *actor = *iterator;

        if(actor->destructible && !actor->destructible->isDead())
        {
            float distance = actor->getDistance(x, y);
            if((closestDistance < 0 || closestDistance > distance) && (distance <= range || range == 0.0f))
            {
                closestMonster = actor;
                closestDistance = distance;
            }
        }
    }

    return closestMonster;
}
