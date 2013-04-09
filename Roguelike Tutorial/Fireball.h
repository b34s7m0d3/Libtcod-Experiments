#ifndef FIREBALL_H
#define FIREBALL_H

class Fireball : public LightningBolt
{
    public:
        Fireball(float range, float damage);
        bool use(Actor *owner, Actor *wearer);
    protected:
    private:
};

#endif // FIREBALL_H
