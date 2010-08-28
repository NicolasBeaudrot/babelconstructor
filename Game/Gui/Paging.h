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
#ifndef PAGING_H
#define PAGING_H
#include "Widget.h"

    class Paging : public Widget
    {
        private :
            unsigned int _current_page
                        ,_page_focused
                        ,_element_per_page
                        ,_total;
            sf::Font *_font;
            std::vector<sf::String*> _arrPage;
            bool _hover;
        public :
            Paging(std::string name, int total, int element_per_page = 5);
            bool intersect(float x, float y);
            void onClic(int bouton);
            void onHover();
            void setPosition(float x, float y);
            sf::Vector2f getPosition();
            sf::Vector2f getPageLimit();
            unsigned int getTotal();
            void display(sf::RenderWindow* app);
    };

#endif
