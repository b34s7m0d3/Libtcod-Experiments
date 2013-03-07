#include "main.h"

Destructible::Destructible(float maxHp, float defense, bool isImmortal, const char *corpseName) :
    maxHp(maxHp), hp(maxHp), defense(defense), isImmortal(isImmortal), corpseName(corpseName)
{
}

MonsterDestructible::MonsterDestructible(float maxHp, float defense, bool isImmortal, const char *corpseName) :
    Destructible(maxHp, defense, isImmortal, corpseName)
{
}

PlayerDestructible::PlayerDestructible(float maxHp, float defense, bool isImmortal, const char *corpseName) :
    Destructible(maxHp, defense, isImmortal, corpseName)
{
}

float Destructible::takeDamage(Actor *owner, float damage)
{
    damage -= defense;
    if ( damage > 0 )
    {
        hp -= damage;
        if ( hp <= 0 )
        {
            die(owner);
        }
    }
    else
    {
        damage = 0;
    }

    return damage;
}

float Destructible::heal(float amount)
{
    hp += amount;

    if(hp > maxHp)
    {
        amount -= hp - maxHp;
        hp = maxHp;
    }

    return amount;
}

void Destructible::die(Actor *owner)
{
    // transform the actor into a corpse!
    owner->ch = '%';
    owner->col = TCODColor::darkRed;
    owner->name = corpseName;
    owner->blocks = false;
    // make sure corpses are drawn before living actors
    engine.sendToBack(owner);
}

void MonsterDestructible::die(Actor *owner)
{
    // transform it into a corpse! it doesn't block, can't be attacked, and doesn't move.
    if(!owner->destructible->isImmortal)
    {
        engine.gui->message(TCODColor::lightGrey, "%s is dead", owner->name);
        Destructible::die(owner);
    }
}

void PlayerDestructible::die(Actor *owner)
{
    if(!owner->destructible->isImmortal)
    {
        engine.gui->message(TCODColor::red, "You died!");
        Destructible::die(owner);
        engine.gameStatus=Engine::DEFEAT;
    }
}
