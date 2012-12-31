#ifndef BSPLISTENER_H
#define BSPLISTENER_H

#include "libtcod.hpp"
#include "Map.h"

class BspListener : public ITCODBspCallback
{
    public:
        BspListener(Map &map, int minRoomSize);
        bool visitNode(TCODBsp *node, void *userData);
    protected:
    private:
        Map &map;
        int minRoomSize;
        int roomNum;
        int lastX,lastY; // center of the last room
};

#endif // BSPLISTENER_H
