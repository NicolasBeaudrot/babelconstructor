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
#ifndef ELEMENT_H
#define ELEMENT_H
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Utility/Collision.h"
#include "../Utility/Logger.h"
#include "../Utility/ImageManager.h"
#include <Box2D/Box2D.h>

    class Element
    {
        protected :
            b2Body* _body;
            bool clicked;
            sf::Image *_image;
            sf::Sprite _sprite;
            sf::RenderWindow *_app;

        public :
            Element();

            ~Element();

            /**
            * This function is used to return the y position of the element
            * @return y position
            */
            float getYPosition();

            /**
            * This function is called each clic
            * @param b2Body
            */
            void clic(b2Body *);

            /**
            * This function is used to rotate an element
            * @param value : angle value added
            */
            void rotate(const float value);

            /**
            * This function is used to know if the element is upper than the value
            * @param value : y position of the limit
            * @return the comparaison result
            */
            bool test(const float value);

            /**
            * This function is used to know if the element is below than the value
            * @param value : y position of the ground
            * @return the comparaison result
            */
            bool below(const float value);

            /**
            * This function is used to display the element
            * @param input contains mouse coordonates
            */
            void render(const sf::Input& input);
    };
#endif
