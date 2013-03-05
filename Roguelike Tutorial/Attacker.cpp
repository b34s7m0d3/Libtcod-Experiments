#include "main.h"

Attacker::Attacker(float power) : power(power)
{
    //ctor
}

void Attacker::attack(Actor *owner, Actor *target)
{
    if(target->destructible && !target->destructible->isDead())
    {
        float damage = power - target->destructible->defense;
        if(damage > 0)
        {
            TCODColor textColor = owner == engine.player ? TCODColor::red : TCODColor::lightGrey;
            engine.gui->message(textColor, "%s attacks %s for %g hit points.", owner->name, target->name, power - target->destructible->defense);
        }
        else
        {
            engine.gui->message(TCODColor::lightGrey, "%s attacks %s but it has no effect!", owner->name, target->name);
        }

        target->destructible->takeDamage(target, power);
    }
    else
    {
        engine.gui->message(TCODColor::lightGrey, "%s attacks %s in vain.", owner->name, target->name);
    }
}
