#include "main.h"

Engine::Engine(int screenWidth, int screenHeight) : gameStatus(STARTUP), fovRadius(10), screenWidth(screenWidth), screenHeight(screenHeight)
{
    TCODConsole::initRoot(screenWidth, screenHeight, "libtcod C++ tutorial", false);
    player = new Actor(screenWidth/2, screenHeight/2, '@', TCODColor::white, "player");
    player->destructible = new PlayerDestructible(30, 2, true, "your cadaver");
    player->attacker = new Attacker(5);
    player->ai = new PlayerAi();
    player->container = new Container(26);
    //actors.push(player);
    map = new Map(screenWidth, screenHeight - 7);
    gui = new Gui();

    gui->message(TCODColor::red, "Welcome stranger!\nPrepare to perish in the Tombs of the Ancient Kings.");
}

Engine::~Engine()
{
    actors.clearAndDelete();
    delete map;
    delete gui;
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
            // why do we have to have *actor?
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
