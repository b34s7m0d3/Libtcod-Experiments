#include "libtcod.hpp"
#include "Map.h"
#include "Actor.h"
#include "Engine.h"
#include "BspListener.h"

// TODO: How does a Map object read from the Engine object?

static const int ROOM_MAX_SIZE = 12;
static const int ROOM_MIN_SIZE = 6;

Map::Map(int width, int height)
    : width(width), height(height)
{
    bool isTransparent = false;
    bool isWalkable = false;

    map = new TCODMap::TCODMap (width, height);
    map->clear(isTransparent, isWalkable);

    tiles = new Tile[width * height];

    buildBSPTree();
}

Map::~Map()
{
    delete map;
    delete [] tiles;
}

bool Map::isWall(int x, int y) const
{
    if((x < 0 || x >= width) || (y < 0 || y >= height)){
        return true;
    }

    return !map->isWalkable(x, y);
}

bool Map::isExplored(int x, int y) const
{
    return tiles[x + y * width].explored;
}

bool Map::isInFov(int x, int y) const
{
    if(map->isInFov(x, y))
    {
        tiles[x + y * width].explored = true;
        return true;
    }

    return false;
}

void Map::computeFov()
{
    map->computeFov(engine.player->x, engine.player->y, engine.fovRadius);
}

void Map::dig(int x1, int y1, int x2, int y2)
{
    if(x2 < x1)
    {
        int tmp = x2;
        x2 = x1;
        x1 = tmp;
    }

    if(y2 < y1)
    {
        int tmp = y2;
        y2 = y1;
        y1 = tmp;
    }

    for(int x = x1; x <= x2; x++)
    {
        for(int y = y1; y <= y2; y++)
        {
            bool isTransparent = true;
            bool isWalkable = true;

            map->setProperties(x, y, isTransparent, isWalkable);
        }
    }
}

void Map::createRoom(bool first, int x1, int y1, int x2, int y2)
{
    dig(x1, y1, x2, y2);

    if(first)
    {
        engine.player->x = (x1 + x2)/2;
        engine.player->y = (y1 + y2)/2;
    }
    else
    {
        TCODRandom * rng = TCODRandom::getInstance();

        if(rng->getInt(0, 3) == 0)
        {
            engine.actors.push(new Actor((x1 + x2)/2, (y1 + y2)/2, '@', TCODColor::yellow));
        }
    }
}

void Map::render() const
{
    static const TCODColor darkwall(0, 0, 100);
    static const TCODColor darkGround(50, 50, 150);
    static const TCODColor lightWall(130,110,50);
    static const TCODColor lightGround(200,180,50);

    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            TCODColor color;
            if(isInFov(x, y))
            {
                color = isWall(x, y) ? lightWall : lightGround;
            }
            else if(isExplored(x, y))
            {
                color = isWall(x, y) ? darkwall : darkGround;
            }

            TCODConsole::root->setCharBackground(x, y, color);
        }
    }
}

void Map::buildBSPTree()
{
    // create root node of BSP tree, this node represents the position and size of dungeon
    TCODBsp::TCODBsp bsp(0, 0, width, height);

    // splitRecursive(TCODRandom *randomizer, int numOfRecursionLvls, int minNodeHeight, int minNodeWidth, float maxNodeH/WRatio, float maxNodeW/HRatio)
    bsp.splitRecursive(NULL, 8, ROOM_MAX_SIZE, ROOM_MAX_SIZE, 1.5f, 1.5f);

    // Define ITCODBspCallback's virtual method: bool visitNode(TCODBsp *node, void *userData)
    BspListener::BspListener listener(* this, ROOM_MIN_SIZE);

    // Call BspListener's visitNode() for each node in BSP tree, starting with last most level of nodes created
    bsp.traverseInvertedLevelOrder(&listener, NULL);
}
