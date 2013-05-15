#ifndef CONTAINER_H
#define CONTAINER_H


class Container : public Persistent
{
    public:
        int size; // max number of actors. 0 = unlimited.
        TCODList<Actor *> inventory;

        Container(int size);
        ~Container();
        bool add(Actor *actor);
        void remove(Actor *actor);
        void load(TCODZip &zip);
        void save(TCODZip &zip);
    protected:
    private:
};

#endif // CONTAINER_H
