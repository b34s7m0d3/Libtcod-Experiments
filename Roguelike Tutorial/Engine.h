#ifndef ENGINE_H
#define ENGINE_H

class Engine
{
    public:
        TCODList<Actor *> actors;
        Actor *player;
        Map *map;

        Engine();
        ~Engine();
        bool update();
        void render();
};

extern Engine engine;

#endif // ENGINE_H
