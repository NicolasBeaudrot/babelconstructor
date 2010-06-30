#ifndef GameManager_h
#define GameManager_h
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Map/MapManager.h"
#include "Element/ElementFactory.h"
#include "Utility/Logger.h"
#include <Box2D/Box2D.h>

class GameManager
{
    private :
        sf::RenderWindow _app;
        sf::Clock _clock;
        sf::View _camera;
        b2World *world;

    public :
        GameManager();

        virtual ~GameManager();

        void createWorld();

        void destroyWorld();

        void run();
};

#endif
