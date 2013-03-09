#ifndef AI_H
#define AI_H

class Ai
{
    public:
        // "= 0" means that the method is a pure virtual method, or an abstract method. The Ai class has no implementation for this method.
        virtual void update(Actor *owner) = 0;

    protected:
    private:
};

class PlayerAi : public Ai
{
    public :
        void update(Actor *owner);

    protected :
        bool moveOrAttack(Actor *owner, int targetx, int targety);
        void handleActionKey(Actor *owner, int ascii);
        Actor *choseFromInventory(Actor *owner);
};

class MonsterAi : public Ai
{
    public :
        void update(Actor *owner);

    protected :
        int moveCount;
        void moveOrAttack(Actor *owner, int targetx, int targety);
};

#endif // AI_H
