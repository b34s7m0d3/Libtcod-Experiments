#ifndef ATTACKER_H
#define ATTACKER_H

class Attacker
{
    public:
        float power; // hit points given

        Attacker(float power);
        void attack(Actor *owner, Actor *target);
};

#endif // ATTACKER_H
