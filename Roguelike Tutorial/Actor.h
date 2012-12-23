#ifndef ACTOR_H
#define ACTOR_H


class Actor
{
    public:
        int x, y; // position on map
        int ch; // ascii code
        TCODColor col; // color

        Actor(int x, int y, int ch, const TCODColor &col);
        void render() const; // the const keyword here means that the function does not modify the content of the Actor object
};

#endif // ACTOR_H
