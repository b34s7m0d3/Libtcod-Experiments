#ifndef HEALER_H
#define HEALER_H


class Healer : public Pickable
{
    public:
        float amount;

        Healer(float amount);
        bool use(Actor *owner, Actor *wearer);
    protected:
    private:
};

#endif // HEALER_H
