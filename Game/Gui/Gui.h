/*
    Copyright (C) 2010  Nicolas Beaudrot, Vincent Durey

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef GUI_H
#define GUI_H
#include "Menu.h"
#include "Button.h"
#include "Image.h"
#include "Label.h"

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
            Menu* getCurrentMenu();
            void event(sf::Event* ev, const sf::Input& in);
            void setCurrentMenu(int i);
            void setVisibility(bool visible);
            void display();
    };

#endif
