#ifndef DESTRUCTIBLE_H
#define DESTRUCTIBLE_H

class Destructible : public Persistent
{
    public:
        float maxHp; // maximum health points
        float hp; // current health points
        float defense; // hit points deflected
        bool isImmortal;
        char *corpseName; // the actor's name once dead/destroyed

        Destructible(float maxHp, float defense, bool isImmortal, const char *corpseName);
        ~Destructible();
        inline bool isDead() { return !isImmortal && hp <= 0; }

        float takeDamage(Actor *owner, float damage);
        float heal(float amount);
        void load(TCODZip &zip);
        void save(TCODZip &zip);
        virtual void die(Actor *owner);
        static Destructible *create(TCODZip &zip);
    protected:
        enum DestructibleType{ MONSTER, PLAYER };
    private:
};

class MonsterDestructible : public Destructible {
public :
	MonsterDestructible(float maxHp, float defense, bool isImmortal, const char *corpseName);
	void die(Actor *owner);
	void save(TCODZip &zip);
};

class PlayerDestructible : public Destructible {
public :
	PlayerDestructible(float maxHp, float defense, bool isImmortal, const char *corpseName);
	void die(Actor *owner);
	void save(TCODZip &zip);
};

#endif // DESTRUCTIBLE_H
