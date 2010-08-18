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
#ifndef MAP
#define MAP
#include "../Element/ElementFactory.h"
#include "../Obstacle/ObstacleFactory.h"
#include "../Utility/Logger.h"

class Map {
	private:
		sf::RenderWindow * _app;

    public :
        /**
        * Constructor : it will load a map
        * @param application : SFML window
        * @param nom : map filename
        */
        Map(sf::RenderWindow * application, const std::string &nom);

        /**
        * Destructor
        */
        ~Map();
};

#endif
