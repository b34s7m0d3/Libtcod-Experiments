#ifndef GUI_H
#define GUI_H


class Gui : public Persistent
{
    public:
        Menu menu;

        Gui();
        ~Gui();
        void render();
        void clear();
        void load(TCODZip &zip);
        void save(TCODZip &zip);
        void message(const TCODColor &col, const char *text, ...);

    protected:
        TCODConsole *con;
        struct Message
        {
            char *text;
            TCODColor col;
            Message(const char *text, const TCODColor &col);
            ~Message();
        };
        TCODList<Message *> log;
        void renderBar(int x, int y, int width, const char *name, float value, float maxValue, const TCODColor &barColor, const TCODColor &backColor);
        void renderMouseLook();

    private:
};

#endif // GUI_H
