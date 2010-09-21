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
#ifndef GameManager_h
#define GameManager_h
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Box2D/Box2D.h>
#include "Map/MapManager.h"
#include "Utility/Logger.h"
#include "Element/ElementFactory.h"
#include "Obstacle/ObstacleFactory.h"
#include "Utility/PausableClock.h"
#include "Utility/ScoreManager.h"
#include <SFML/Audio.hpp>

class GameManager : public CSingleton<GameManager>
{
    private :
        friend class CSingleton<GameManager>;
        GameManager();
        ~GameManager();

        //Private functions
        void createWorld();
        void destroyWorld();
        void loadMap(std::string path = "");

        sf::RenderWindow _app;
        sf::Clock _clock;
        sf::Clock _intro;
        sftools::PausableClock _counter;
        b2World *world;
        int _paused;
        bool _winner, _first_loop;

    public :
        void Init();

        void run(std::string path = "");

        sf::RenderWindow &getApp();
};

#endif
