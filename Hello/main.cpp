#include "libtcod.hpp"

int main() {

    int width = 80;
    int height = 50;

    TCODConsole::initRoot(width, height, "Libtcod Hello World");

    int x = width / 2;
    int y = height /2;
    TCOD_key_t key;
    do
    {
        TCODConsole::root->clear();
        TCODConsole::root->printCenter(x, y, TCOD_BKGND_NONE, "Libtcod says: Hello, World!");
        TCODConsole::flush();

        y++;

        key = TCODConsole::waitForKeypress(true);
    }
    while(key.c == '\0');

    TCODConsole::waitForKeypress(true);
}
