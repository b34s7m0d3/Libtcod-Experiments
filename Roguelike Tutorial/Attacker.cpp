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
            printf("%s attacks %s for %g hit points.\n", owner->name, target->name, damage);
        }
        else
        {
            printf("%s attacks %s but it has no effect!\n", owner->name, target->name);
        }

        target->destructible->takeDamage(target, power);
    }
    else
    {
        printf("%s attacks %s in vain.\n", owner->name, target->name);
    }
}
