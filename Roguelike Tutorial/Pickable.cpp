#include "main.h"

bool Pickable::pick(Actor *owner, Actor *wearer)
{
    if(wearer->container && wearer->container->add(owner))
    {
        engine.actors.remove(owner);
        return true;
    }

    return false;
}

void Pickable::drop(Actor *owner, Actor *wearer)
{
    if ( wearer->container )
    {
        // Update wearer's inventory
        wearer->container->remove(owner);

        // Return item to map
        engine.actors.push(owner);
        owner->x=wearer->x;
        owner->y=wearer->y;

        engine.gui->message(TCODColor::lightGrey, "%s drops a %s.", wearer->name, owner->name);
    }
}

bool Pickable::use(Actor *owner, Actor *wearer)
{
    if(wearer->container)
    {
        wearer->container->remove(owner);
        delete owner;
        return true;
    }

    return false;
}
