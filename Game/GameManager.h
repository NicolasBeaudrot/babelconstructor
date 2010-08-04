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

class GameManager
{
    private :
        sf::RenderWindow _app;
        sf::Clock _clock;
        sf::Clock _intro;
        sf::View _camera;
        b2World *world;

    public :
        GameManager();

        virtual ~GameManager();

        void createWorld();

        void destroyWorld();

        void loadMap();

        void run();
};

#endif
