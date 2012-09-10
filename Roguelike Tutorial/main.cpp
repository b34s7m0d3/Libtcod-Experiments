// Code based on tutorial: http://roguebasin.roguelikedevelopment.org/index.php/Complete_Roguelike_Tutorial,_using_python%2Blibtcod,_part_1
#include "libtcod.hpp"

int SCREEN_WIDTH = 80;
int SCREEN_HEIGHT = 50;
int playerx, playery;
bool HandleKeys();

int main()
{
    TCODConsole::setCustomFont("arial10x10.png", TCOD_FONT_LAYOUT_TCOD, 0, 0);
    TCODConsole::initRoot(SCREEN_WIDTH, SCREEN_HEIGHT, "Libtcod Tutorial");

    playerx = SCREEN_WIDTH / 2;
    playery = SCREEN_HEIGHT / 2;

    bool exit;
    while(!TCODConsole::isWindowClosed())
    {
        TCODConsole::root->clear();
        TCODConsole::root->setForegroundColor(TCODColor::white);
        TCODConsole::root->printLeft(playerx, playery, TCOD_BKGND_NONE, "@");

        TCODConsole::flush();

        exit = HandleKeys();
        if(exit)
            break;
    }

    return 0;
}

bool HandleKeys(){
    TCOD_key_t key = TCODConsole::waitForKeypress(true);

    if(key.vk == TCODK_DOWN && playery < SCREEN_HEIGHT - 1)
        playery += 1;
    else if(key.vk == TCODK_UP && playery > 0)
        playery -= 1;
    else if(key.vk == TCODK_RIGHT && playerx < SCREEN_WIDTH - 1)
        playerx += 1;
    else if(key.vk == TCODK_LEFT && playerx > 0)
        playerx -= 1;
    else if(key.vk == TCODK_ENTER && key.lalt)
        TCODConsole::setFullscreen(!TCODConsole::isFullscreen());
    else if(key.vk == TCODK_ESCAPE)
        return true;

    return false;
}
