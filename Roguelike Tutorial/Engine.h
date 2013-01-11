#ifndef ENGINE_H
#define ENGINE_H

class Engine
{
    public:
        TCODList<Actor *> actors;
        Actor *player;
        Map *map;
        int fovRadius;

        Engine();
        ~Engine();
        bool update();
        void render();

        private:
            bool computeFov;
};

extern Engine engine;

#endif // ENGINE_H
