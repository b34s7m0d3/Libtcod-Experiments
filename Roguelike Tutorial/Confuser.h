#ifndef CONFUSER_H
#define CONFUSER_H

class Confuser : public Pickable
{
    public:
        int nbTurns;
        float range;

        Confuser(int nbTurns, float range);
        bool use(Actor *owner, Actor *wearer);
};

#endif // CONFUSER_H
