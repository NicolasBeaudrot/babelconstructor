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
#ifndef WIDGET_H
#define WIDGET_H
#include <string>
#include "../GameManager.h"


    class Widget
    {
        protected :
            std::string _name;
            bool _visible;

            std::vector<sf::Image*> _arrImages;
            std::vector<sf::Sprite> _arrSprites;

        public :
            Widget(std::string name);
            virtual ~Widget();
            virtual bool intersect(float x, float y);
            virtual void onClic(int bouton);
            virtual void onHover();
            virtual void setPosition(float x, float y) = 0;
            virtual sf::Vector2f getPosition() = 0;
            virtual void display(sf::RenderWindow* app) = 0;

            std::string getName();
            bool getVisibility();
            void setName(std::string name);
            void setVisibility(bool visible);
            void addTexture(std::string path);

    };

#endif
