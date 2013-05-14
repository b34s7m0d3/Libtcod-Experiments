#include "main.h"
#include <math.h>

Actor::Actor(int x, int y, int ch, const TCODColor &col, const char *name)
    : x(x), y(y), ch(ch), col(col), name(name), blocks(true), attacker(NULL), destructible(NULL), ai(NULL), pickable(NULL), container(NULL)
{
    //ctor
}

Actor::~Actor()
{
    if(attacker) delete attacker;
    if(destructible) delete destructible;
    if(ai) delete ai;
    if(pickable) delete pickable;
    if(container) delete container;
}

void Actor::render() const
{
    TCODConsole::root->setChar(x, y, ch);
    TCODConsole::root->setCharForeground(x, y, col);
}

void Actor::update()
{
    if(ai) ai->update(this);
}

void Actor::load(TCODZip &zip)
{
    x = zip.getInt();
    y = zip.getInt();
    ch = zip.getInt();
    col = zip.getColor();
    name = zip.getString();
    blocks = zip.getInt();
    bool hasAttacker = zip.getInt();
    bool hasDestructible = zip.getInt();
    bool hasAI = zip.getInt();
    bool hasPickable = zip.getInt();
    bool hasContainer = zip.getInt();

    if(hasAttacker)
    {
        attacker = new Attacker(0.0f);
        // load attacker
    }

    if(hasDestructible)
    {
        // load destructible
    }

    if(hasAI)
    {
        // load ai
    }

    if(hasPickable)
    {
        // load pickable
    }

    if(hasContainer)
    {
        // load container
    }
}

void Actor::save(TCODZip &zip)
{
    zip.putInt(x);
    zip.putInt(y);
    zip.putInt(ch);
    zip.putColor(&col);
    zip.putString(name);
    zip.putInt(blocks);
    zip.putInt(attacker != NULL);
    zip.putInt(destructible != NULL);
    zip.putInt(ai != NULL);
    zip.putInt(pickable != NULL);
    zip.putInt(container != NULL);

    if(attacker)
    {
        // save attacker
    }

    if(destructible)
    {
        // save destructible
    }

    if(ai)
    {
        // save ai
    }

    if(pickable)
    {
        // save pickable
    }

    if(container)
    {
        // save container
    }
}

float Actor::getDistance(int cx, int cy) const
{
    int dx = x - cx;
    int dy = y - cy;

    return sqrt((dx * dx) + (dy * dy));
}
