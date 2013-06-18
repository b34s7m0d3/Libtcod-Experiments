#ifndef ENGINE_H
#define ENGINE_H

class Engine
{
    public:
        enum GameStatus { STARTUP, IDLE, NEW_TURN, VICTORY, DEFEAT } gameStatus;
        TCODList<Actor *> actors;
        Actor *player;
        Actor *stairs;
        Map *map;
        int fovRadius;
        int screenWidth;
        int screenHeight;
        Gui *gui;
        TCOD_key_t lastKey;
        TCOD_mouse_t mouse;

        Engine(int screenWidth, int screenHeight);
        ~Engine();
        void init();
        void term();
        void load();
        void save();
        void render();
        void update();
        void sendToBack(Actor *actor);
        bool pickATile(int *x, int *y, float maxRange = 0.0f);
        Actor *getActor(int x, int y) const;
        Actor *getClosestMonster(int x, int y, float range) const;

        private:
};

extern Engine engine;

#endif // ENGINE_H
