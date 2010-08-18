#ifndef MENU_H
#define MENU_H
#include "Widget.h"

    class Menu
    {
        private :
            bool _visible;
            std::vector<Widget*> _arrWidget;

        public :
            Menu();
            ~Menu();
            void add(Widget *w);
            void event(sf::Event *ev, const sf::Input& in);
            void setVisibility(bool visible);
            void display(sf::RenderWindow* app);
    };

#endif
