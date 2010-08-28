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
            ~MapManager();
            sf::RenderWindow* _app;
            std::vector<std::string> _tabOfficialMap, _tabUnofficialMap;
            unsigned int _indexCurr;
            Map* _currentMap;
            bool _official;
            void listDir(std::string path, bool official);

        public:
            /**
            * Constructor
            * @param window : SFML window
            */
            void Init(sf::RenderWindow* window);

            /**
            * This function is used to load a map
            * @param : map filename
            */
            void load(std::string filename);

            /**
            * This function is used to load the next map
            * @return true if there is a new map, false if the game is finished.
            */
            bool nextMap();

            /**
            * This function is used to reload the current map
            */
            void reLoad();

            /**
            * This function is used to stop the game
            */
            void stop();

            /**
            * This function returns the map filename
            * @return filename
            */
            std::string getCurrentMapName();

            /**
            * This function returns the maps list
            */
            std::vector<std::string>& getMapList(bool official=true);

            /**
            * This function returns the current mode
            */
            bool isOfficialMode();

            /**
            * Set the official mode
            */
            void setOfficialMode(bool status);

    };

#endif
