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
#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "../Utility/Collision.h"
#include "../Utility/Logger.h"
#include "../Utility/ImageManager.h"

    class Obstacle
    {
        protected :
            b2Body* _body;
            sf::RenderWindow *_app;
            sf::Image *_image;
            sf::Sprite _sprite;

        public :
            /**
            * Constructor
            */
            Obstacle();

            /**
            * Destructor
            */
            ~Obstacle();

            /**
            * This function is used to display the obstacle
            */
            void render();
    };

#endif
