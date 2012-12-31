#ifndef MAP_H
#define MAP_H

class Map
{
    public:
        int width, height;

        Map(int width, int height);
        ~Map();
        bool isWall(int x, int y) const; // the const keyword here means that the function does not modify the content of the Actor object
        void render() const; // the const keyword here means that the function does not modify the content of the Actor object

        // These methods were changed to public when we moved BspListener declaration from Map.cpp into its own class files
        void dig(int x1, int y1, int x2, int y2);
        void createRoom(bool first, int x1, int y1, int x2, int y2);
    protected:
        TCODMap::TCODMap * map;
        friend class BspListener;

        //void dig(int x1, int y1, int x2, int y2);
        //void createRoom(bool first, int x1, int y1, int x2, int y2);
};

#endif // MAP_H
