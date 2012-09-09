#include "libtcod.hpp"

int main() {

    int width = 80;
    int height = 50;

    TCODConsole::initRoot(width, height, "Libtcod Hello World");
    TCOD_key_t key;
    int x = width / 2;
    int y = height / 2;

    while(!TCODConsole::isWindowClosed())
    {
        TCODConsole::root->clear();
        TCODConsole::root->printCenter(x, y, TCOD_BKGND_NONE, "Libtcod says: Hello, World!"); // Breaks when y is same as height
        TCODConsole::flush();

        y = (y >= (height - 1)) ? 0 : y + 1;

        key = TCODConsole::waitForKeypress(true);

        if(key.vk != TCODK_DOWN)
            return true; // Exit game
    }
}
