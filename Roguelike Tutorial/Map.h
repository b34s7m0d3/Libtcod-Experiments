#ifndef MAP_H
#define MAP_H

struct Tile {
    bool explored; // can we walk through this tile?
    Tile() : explored(false) {}
};

class Map : public Persistent
{
    public:
        int width, height;

        Map(int width, int height);
        ~Map();

        void computeFov();
        void render() const;
        void init(bool withActors);
        void load(TCODZip &zip);
        void save(TCODZip &zip);
        void addItem(int x, int y);
        void addMonster(int x, int y);
        void dig(int x1, int y1, int x2, int y2);
        void createRoom(bool first, int x1, int y1, int x2, int y2, bool withActors);
        bool canWalk(int x, int y) const;
        bool isExplored(int x, int y) const;
        bool isInFov(int x, int y) const;
        bool isWall(int x, int y) const;

    protected:
        Tile *tiles;
        TCODMap * map;
        long seed;
        TCODRandom *rng;
        friend class BspListener;

    private:
        void buildBSPTree();
};

#endif // MAP_H
