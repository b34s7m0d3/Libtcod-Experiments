#ifndef LIGHTNINGBOLT_H
#define LIGHTNINGBOLT_H

class LightningBolt : public Pickable
{
    public :
        float range, damage;

        LightningBolt(float range, float damage);
        bool use(Actor *owner, Actor *wearer);
};

#endif // LIGHTNINGBOLT_H
