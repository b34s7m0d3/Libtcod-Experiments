#ifndef DESTRUCTIBLE_H
#define DESTRUCTIBLE_H

class Destructible
{
    public:
        float maxHp; // maximum health points
        float hp; // current health points
        float defense; // hit points deflected
        bool isImmortal;
        const char *corpseName; // the actor's name once dead/destroyed

        Destructible(float maxHp, float defense, bool isImmortal, const char *corpseName);
        inline bool isDead() { return !isImmortal && hp <= 0; }

        float takeDamage(Actor *owner, float damage);
        float heal(float amount);
        virtual void die(Actor *owner);
    protected:
    private:
};

class MonsterDestructible : public Destructible {
public :
	MonsterDestructible(float maxHp, float defense, bool isImmortal, const char *corpseName);
	void die(Actor *owner);
};

class PlayerDestructible : public Destructible {
public :
	PlayerDestructible(float maxHp, float defense, bool isImmortal, const char *corpseName);
	void die(Actor *owner);
};

#endif // DESTRUCTIBLE_H
