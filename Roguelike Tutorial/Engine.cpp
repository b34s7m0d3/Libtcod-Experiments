#include "libtcod.hpp"
#include "Actor.h"
#include "Map.h"
#include "Engine.h"

int SCREEN_WIDTH = 80;
int SCREEN_HEIGHT = 50;

Engine::Engine()
{
    TCODConsole::initRoot(SCREEN_WIDTH, SCREEN_HEIGHT, "libtcod C++ tutorial", false);
    player = new Actor(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, '@', TCODColor::white);
    actors.push(player);
    map = new Map(SCREEN_WIDTH, SCREEN_HEIGHT - 5);
}

Engine::~Engine()
{
    actors.clearAndDelete();
    delete map;
}

bool Engine::update()
{
    bool escapePressed = false;

    TCOD_key_t key;
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
    switch(key.vk)
    {
        case TCODK_UP :
            if(!map->isWall(player->x, player->y-1))
            {
                player->y--;
            }
            break;
        case TCODK_DOWN :
            if(!map->isWall(player->x, player->y+1))
            {
                player->y++;
            }
            break;
        case TCODK_LEFT :
            if(!map->isWall(player->x-1, player->y))
            {
                player->x--;
            }
            break;
        case TCODK_RIGHT :
            if(!map->isWall(player->x+1, player->y))
            {
                player->x++;
            }
            break;
        case TCODK_ESCAPE :
            escapePressed = true;
            break;
        default: break;
    }

    return escapePressed;
}

void Engine::render()
{
    TCODConsole::root->clear(); // root is a static pointer member of TCODConsole

    // draw the map
    map->render();

    // draw the actors
    for(Actor **iterator=actors.begin(); iterator != actors.end(); iterator++) // **iterator is a pointer to a pointer?
    {
        (*iterator)->render();
    }
}
