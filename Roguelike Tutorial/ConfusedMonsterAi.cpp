#include "main.h"

ConfusedMonsterAi::ConfusedMonsterAi(int nbTurns, Ai *oldAi) : nbTurns(nbTurns), oldAi(oldAi)
{
}

void ConfusedMonsterAi::update(Actor *owner)
{
    TCODRandom *rng = TCODRandom::getInstance();

    int dx = rng->getInt(-1, 1);
    int dy = rng->getInt(-1, 1);

    if(dx != 0 || dy != 0)
    {
        int destX = owner->x + dx;
        int destY = owner->y + dy;
        if(engine.map->canWalk(destX, destY))
        {
            owner->x = destX;
            owner->y = destY;
        }
        else
        {
            Actor *actor = engine.getActor(destX, destY);
            if(actor)
            {
                owner->attacker->attack(owner, actor);
            }
        }
    }

    nbTurns--;
    if(nbTurns == 0)
    {
        owner->ai = oldAi;
        delete this;
    }
}
