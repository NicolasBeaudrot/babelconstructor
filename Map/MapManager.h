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
#ifndef MAP_MANAGER
#define MAP_MANAGER
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Utility/Singleton.h"
#include "Map.h"
#include <dirent.h>

    class MapManager : public CSingleton<MapManager>
    {
        private:
            friend class CSingleton<MapManager>;
            MapManager();
            virtual ~MapManager();
            sf::RenderWindow* _app;
            sf::View* _camera;
            std::vector<std::string> _tabMap;
            int _indexCurr;

        public:
            /**
            * Constructor
            * @param window : SFML window
            * @param camera : SFML camera
            */
            void Init(sf::RenderWindow* window, sf::View* camera);

            /**
            * This fucntion is used to load a map using a filename
            * @param nom : map filename
            * @param world : box2D object
            */
            void Load(const std::string& nom, b2World& world);

            /**
            * Public attribute
            * This pointor is used to access to the current map
            */
            Map* getCurrentMap;

            /**
            * This function is used to load the next map
            * @param world : box2D object
            */
            bool nextMap(b2World& world);
    };

#endif
