#include "main.h"
#include <math.h>

Actor::Actor(int x, int y, int ch, const TCODColor &col, const char *name)
    : x(x), y(y), ch(ch), col(col), blocks(true), attacker(NULL), destructible(NULL), ai(NULL), pickable(NULL), container(NULL)
{
    this->name = strdup(name);
}

Actor::~Actor()
{
    if(attacker) delete attacker;
    if(destructible) delete destructible;
    if(ai) delete ai;
    if(pickable) delete pickable;
    if(container) delete container;

    free(name);
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
    name = strdup(zip.getString());
    blocks = zip.getInt();
    bool hasAttacker = zip.getInt();
    bool hasDestructible = zip.getInt();
    bool hasAI = zip.getInt();
    bool hasPickable = zip.getInt();
    bool hasContainer = zip.getInt();

    if(hasAttacker)
    {
        attacker = new Attacker(0.0f);
        attacker->load(zip);
    }

    if(hasDestructible)
    {
        destructible = Destructible::create(zip);
    }

    if(hasAI)
    {
        ai = Ai::create(zip);
    }

    if(hasPickable)
    {
        pickable = Pickable::create(zip);
    }

    if(hasContainer)
    {
        container = new Container(0);
        container->load(zip);
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
        attacker->save(zip);
    }

    if(destructible)
    {
        destructible->save(zip);
    }

    if(ai)
    {
        ai->save(zip);
    }

    if(pickable)
    {
        pickable->save(zip);
    }

    if(container)
    {
        container->save(zip);
    }
}

float Actor::getDistance(int cx, int cy) const
{
    int dx = x - cx;
    int dy = y - cy;

    return sqrt((dx * dx) + (dy * dy));
}
