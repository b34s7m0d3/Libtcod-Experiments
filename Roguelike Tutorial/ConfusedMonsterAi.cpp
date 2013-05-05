#include "main.h"
#include <windows.h>

ConfusedMonsterAi::ConfusedMonsterAi(int nbTurns, Ai *oldAi) : nbTurns(nbTurns), oldAi(oldAi)
{
}

void ConfusedMonsterAi::update(Actor *owner)
{
    bool actorIsPlayer = (owner == engine.player);
    if(actorIsPlayer)
    {
        engine.gameStatus = Engine::NEW_TURN;
        Sleep(2000);
    }

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
        if(actorIsPlayer)
            engine.gui->message(TCODColor::lightGreen, "The %s regains their composure and resumes\ntheir adventure.", owner->name);

        owner->ai = oldAi;
        delete this;
    }
}
