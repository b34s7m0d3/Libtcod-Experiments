/* Tutorial Source: http://codeumbra.eu/complete-roguelike-tutorial-using-c-and-libtcod-part-1-setting-up
 * Creating classes in CodeBlocks: http://www.youtube.com/watch?v=2fTsbQUP_no
 */
#include "main.h"

Engine engine(80, 50);

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
