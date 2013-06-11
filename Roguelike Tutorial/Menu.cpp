#include "main.h"

Menu::~Menu()
{
    clear();
}

void Menu::clear()
{
    items.clearAndDelete();
}

void Menu::addItem(MenuItemCode code, const char *label)
{
    MenuItem *item = new MenuItem();

    item->code = code;
    item->label = label;
    items.push(item);
}

Menu::MenuItemCode Menu::pick()
{
    static TCODImage img("menu_background1.png");

    int selectedItem = 0;
    while(!TCODConsole::isWindowClosed())
    {
        img.blit2x(TCODConsole::root, 0, 0);

        int currentItem = 0;
        for(MenuItem **iterator = items.begin(); iterator != items.end(); iterator++)
        {
            if(currentItem == selectedItem)
            {
                TCODConsole::root->setDefaultForeground(TCODColor::lighterOrange);
            }
            else
            {
                TCODConsole::root->setDefaultForeground(TCODColor::lightGrey);
            }

            TCODConsole::root->print(10, 10 + currentItem + 3, (*iterator)->label);
            currentItem++;
        }

        TCODConsole::flush();

        TCOD_key_t key;
        TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
        switch(key.vk)
        {
            case TCODK_UP:
                selectedItem--;
                if(selectedItem < 0)
                {
                    selectedItem = items.size() - 1;
                }
                break;
            case TCODK_DOWN:
                selectedItem = (selectedItem + 1) % items.size();
                break;
            case TCODK_ENTER:
            case TCODK_KPENTER:
                return items.get(selectedItem)->code;
                break;
            default: break;
        }
    }

    return NONE;
}
