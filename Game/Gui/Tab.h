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
#ifndef TAB_H
#define TAB_H
#include "Widget.h"
#include "Gui.h"

    class Tab : public Widget
    {
        private :
            int _menu_id;
            Gui *_gui;

        public :
            Tab(std::string name, std::string texture1, std::string texture2, Gui *gui, int menu);
            bool intersect(float x, float y);
            void onClic(int bouton);
            void onHover();
            void setPosition(float x, float y);
            sf::Vector2f getPosition();
            float getHeight();
            float getWidth();
            void display(sf::RenderWindow* app);
    };
#endif

