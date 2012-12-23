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
    protected:
        TCODMap::TCODMap * map;

        void setWall(int x, int y);
};

#endif // MAP_H
