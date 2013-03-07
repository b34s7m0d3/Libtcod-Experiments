#ifndef ACTOR_H
#define ACTOR_H

class Actor
{
    public:
        int x, y; // position on map
        int ch; // ascii code
        TCODColor col; // color
        const char *name; // actor name
        bool blocks;
        Attacker *attacker;
        Destructible *destructible;
        Ai *ai;
        Pickable *pickable;
        Container *container;

        Actor(int x, int y, int ch, const TCODColor &col, const char *name);
        ~Actor();
        void render() const; // the const keyword here means that the function does not modify the content of the Actor object
        void update();
};

#endif // ACTOR_H
