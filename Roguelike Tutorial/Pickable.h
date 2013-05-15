#ifndef PICKABLE_H
#define PICKABLE_H

class Pickable : public Persistent
{
    public:
        bool pick(Actor *owner, Actor *wearer);
        void drop(Actor *owner, Actor *wearer);
        virtual bool use(Actor *owner, Actor *wearer);
        static Pickable *create(TCODZip &zip);

    protected:
        enum PickableType { HEALER, LIGHTNING_BOLT, CONFUSER, FIREBALL };
    private:
};

class Healer : public Pickable
{
    public:
        float amount;

        Healer(float amount);
        bool use(Actor *owner, Actor *wearer);
        void load(TCODZip &zip);
        void save(TCODZip &zip);
    protected:
    private:
};

class Confuser : public Pickable
{
    public:
        int nbTurns;
        float range;

        Confuser(int nbTurns, float range);
        bool use(Actor *owner, Actor *wearer);
        void load(TCODZip &zip);
        void save(TCODZip &zip);
};

class LightningBolt : public Pickable
{
    public :
        float range, damage;

        LightningBolt(float range, float damage);
        bool use(Actor *owner, Actor *wearer);
        void load(TCODZip &zip);
        void save(TCODZip &zip);
};

class Fireball : public LightningBolt
{
    public:
        Fireball(float range, float damage);
        bool use(Actor *owner, Actor *wearer);
        void save(TCODZip &zip);
};

#endif // PICKABLE_H
