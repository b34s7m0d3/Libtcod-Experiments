#ifndef ATTACKER_H
#define ATTACKER_H

class Attacker : public Persistent
{
    public:
        float power; // hit points given

        Attacker(float power);
        void load(TCODZip &zip);
        void save(TCODZip &zip);
        void attack(Actor *owner, Actor *target);
};

#endif // ATTACKER_H
