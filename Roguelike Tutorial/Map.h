#ifndef MAP_H
#define MAP_H

struct Tile {
    bool explored; // can we walk through this tile?
    Tile() : explored(false) {}
};

class Map
{
    public:
        int width, height;

        Map(int width, int height);
        ~Map();

        bool canWalk(int x, int y) const; // the const keyword here means that the function does not modify the content of the Map object
        bool isExplored(int x, int y) const;
        bool isInFov(int x, int y) const;
        bool isWall(int x, int y) const;
        void addMonster(int x, int y);
        void addItem(int x, int y);
        void computeFov();
        void render() const;

        // These methods were changed to public when we moved BspListener declaration from Map.cpp into its own class files
        void dig(int x1, int y1, int x2, int y2);
        void createRoom(bool first, int x1, int y1, int x2, int y2);

    protected:
        Tile *tiles;
        TCODMap::TCODMap * map;
        friend class BspListener;

    private:
        void buildBSPTree();
};

#endif // MAP_H
