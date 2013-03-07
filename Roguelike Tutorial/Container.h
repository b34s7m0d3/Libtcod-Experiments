#ifndef CONTAINER_H
#define CONTAINER_H


class Container
{
    public:
        int size; // max number of actors. 0 = unlimited.
        TCODList<Actor *> inventory;

        Container(int size);
        ~Container();
        bool add(Actor *actor);
        void remove(Actor *actor);
    protected:
    private:
};

#endif // CONTAINER_H
