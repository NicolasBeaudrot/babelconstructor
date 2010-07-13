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
#ifndef OBSTACLEFACTORY_H
#define OBSTACLEFACTORY_H
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "../Utility/Singleton.h"
#include "Obstacle.h"
#include "SquareObstacle.h"

    class ObstacleFactory : public CSingleton<ObstacleFactory>
    {
         private :
            friend class CSingleton<ObstacleFactory>;
            ObstacleFactory();
            virtual ~ObstacleFactory();

            b2World *_world;
            sf::RenderWindow *_app;
            std::vector<Obstacle*> _tabObst;

        public :
            /**
            * Constructor
            * @param application : SFML window
            * @param : world : Box2D world
            */
            void Init(sf::RenderWindow *application, b2World *world);

            /**
            * Destructor
            */
            void Delete();

            /**
            * This function is used to add an obstacle
            *
            */
            void add(std::string type, sf::Vector2f& position, float& angle, std::string file, sf::Vector2f& base_position);

            /**
            * This function is used to display obstacles
            */
            void render();

    };

#endif
