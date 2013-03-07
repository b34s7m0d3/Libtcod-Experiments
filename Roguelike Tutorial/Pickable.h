#ifndef PICKABLE_H
#define PICKABLE_H


class Pickable
{
    public:
        bool pick(Actor *owner, Actor *wearer);
        virtual bool use(Actor *owner, Actor *wearer);

    protected:
    private:
};

#endif // PICKABLE_H
