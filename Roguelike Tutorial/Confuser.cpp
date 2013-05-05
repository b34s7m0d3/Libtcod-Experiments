#include "main.h"

Confuser::Confuser(int nbTurns, float range) : nbTurns(nbTurns), range(range)
{
}

bool Confuser::use(Actor *owner, Actor *wearer)
{
    engine.gui->message(TCODColor::cyan, "Left-click an enemy to confuse it,\nor right-click to cancel.");

    int x, y;
    if(!engine.pickATile(&x, &y, range))
    {
        return false;
    }

    Actor *actor = engine.getActor(x, y);
    if(!actor)
    {
        return false;
    }

    Ai *confuserAi = new ConfusedMonsterAi(nbTurns, actor->ai, actor->col);
    actor->ai = confuserAi;
    actor->col = TCODColor::lightBlue;

    engine.gui->message(TCODColor::lightGreen, "The eyes of the %s look vacant,\nas he starts to stumble around!", actor->name);

    return Pickable::use(owner, wearer);
}
