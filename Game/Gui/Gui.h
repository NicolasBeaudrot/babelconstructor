#ifndef GUI_H
#define GUI_H
#include "Menu.h"
#include "Button.h"

    class Gui
    {
        private :
            sf::RenderWindow* _app;
            bool _visible;
            std::vector<Menu*> _arrMenus;
            Menu *_currentMenu;

        public :
            Gui(sf::RenderWindow* app);
            ~Gui();
            void add(Menu *m);
            void event(sf::Event* ev, const sf::Input& in);
            void setCurrentMenu(int i);
            void setVisibility(bool visible);
            void display();
    };

#endif
