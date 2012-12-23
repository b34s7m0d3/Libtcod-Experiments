/* Tutorial Source: http://codeumbra.eu/complete-roguelike-tutorial-using-c-and-libtcod-part-1-setting-up
 * Creating classes in CodeBlocks: http://www.youtube.com/watch?v=2fTsbQUP_no
 */
#include "libtcod.hpp"
#include "Actor.h"
#include "Map.h"
#include "Engine.h"

Engine engine;

int main()
{
    bool exitFlagged;
    while(!TCODConsole::isWindowClosed())
    {
        exitFlagged = engine.update();
        if(exitFlagged)
            break;

        engine.render();
        TCODConsole::flush();
    }

    return 0;
}
