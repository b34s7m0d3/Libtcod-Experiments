#include "main.h"

Healer::Healer(float amount) : amount(amount)
{
}

bool Healer::use(Actor *owner, Actor *wearer)
{
    if(wearer->destructible)
    {
        float amountHealed = wearer->destructible->heal(amount); // TODO: Implement heal() in destructible

        if(amountHealed > 0)
        {
            return Pickable::use(owner, wearer);
        }
    }

    return false;
}
