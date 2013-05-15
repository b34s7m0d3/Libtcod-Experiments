#ifndef AI_H
#define AI_H

class Ai : public Persistent
{
    public:
        // "= 0" means that the method is a pure virtual method, or an abstract method. The Ai class has no implementation for this method.
        virtual void update(Actor *owner) = 0;
        static Ai *create(TCODZip &zip);
    protected:
        enum AiType { MONSTER, CONFUSED_MONSTER, PLAYER };
    private:
};

class PlayerAi : public Ai
{
    public :
        void update(Actor *owner);
        void load(TCODZip &zip);
        void save(TCODZip &zip);

    protected :
        bool moveOrAttack(Actor *owner, int targetx, int targety);
        void handleActionKey(Actor *owner, int ascii);
        Actor *choseFromInventory(Actor *owner);
};

class MonsterAi : public Ai
{
    public :
        void update(Actor *owner);
        void load(TCODZip &zip);
        void save(TCODZip &zip);

    protected :
        int moveCount;
        void moveOrAttack(Actor *owner, int targetx, int targety);
};

class ConfusedMonsterAi : public Ai
{
    public:
        ConfusedMonsterAi(int nbTurns, Ai *oldAi, TCODColor oldColor);
        void update(Actor *owner);
        void load(TCODZip &zip);
        void save(TCODZip &zip);

    protected:
        int nbTurns;
        Ai *oldAi;
        TCODColor oldColor;
};

#endif // AI_H
