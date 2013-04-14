#ifndef CONFUSEDMONSTERAI_H
#define CONFUSEDMONSTERAI_H

class ConfusedMonsterAi : public Ai
{
    public:
        ConfusedMonsterAi(int nbTurns, Ai *oldAi);
        void update(Actor *owner);

    protected:
        int nbTurns;
        Ai *oldAi;
};

#endif // CONFUSEDMONSTERAI_H
