#include "libtcod.hpp"
#include "Map.h"

Map::Map(int width, int height)
    : width(width), height(height)
{
    map = new TCODMap::TCODMap (width, height);
    map->clear(true, true);
    setWall(30, 22);
    setWall(50, 22);
}

Map::~Map()
{
    delete map;
}

bool Map::isWall(int x, int y) const
{
    if((x < 0 || x >= width) || (y < 0 || y >= height)){
        return true;
    }

    return !map->isWalkable(x, y);
}

void Map::setWall(int x, int y)
{
    map->setProperties(x, y, true, false);
}

void Map::render() const
{
    static const TCODColor darkwall(0, 0, 100);
    static const TCODColor darkGround(50, 50, 150);

    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            TCODColor color = isWall(x, y) ? darkwall : darkGround;
            TCODConsole::root->setCharBackground(x, y, color);
        }
    }
}
