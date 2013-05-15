#include "main.h"

Container::Container(int size) : size(size)
{
}

Container::~Container()
{
    inventory.clearAndDelete();
}

bool Container::add(Actor *actor)
{
    if(size > 0 && inventory.size() >= size)
    {
        return false; // inventory is full
    }

    inventory.push(actor);
    return true;
}

void Container::remove(Actor *actor)
{
    inventory.remove(actor);
}

void Container::load(TCODZip &zip)
{
    size = zip.getInt();
    int numOfContents = zip.getInt();

    while(numOfContents > 0)
    {
        Actor *actor = new Actor(0, 0, 0, TCODColor::white, NULL);
        actor->load(zip);
        inventory.push(actor);

        numOfContents--;
    }
}

void Container::save(TCODZip &zip)
{
    zip.putInt(size);
    zip.putInt(inventory.size());

    for(Actor **iterator = inventory.begin(); iterator != inventory.end(); iterator++)
    {
        if(*iterator != engine.player)
        {
            (*iterator)->save(zip);
        }
    }
}
