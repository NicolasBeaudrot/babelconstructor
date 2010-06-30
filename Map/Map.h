#ifndef MAP
#define MAP
#include "../Element/ElementFactory.h"
#include "../Utility/Logger.h"

class Map {
	private:
		sf::RenderWindow * _app;
        sf::View * _camera;

    public :
        Map(sf::RenderWindow * application, sf::View* camera, const std::string &nom, b2World& world);
        virtual ~Map();
        void render(const sf::Input& input);
};

#endif
