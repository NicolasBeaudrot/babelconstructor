#ifndef ELEMENT_H
#define ELEMENT_H
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Utility/Collision.h"
#include "../Utility/Logger.h"
#include <Box2D/Box2D.h>

    class Element
    {
        protected :
            sf::Image _image;
            sf::Sprite _sprite;
            b2Body* _body;
            bool clicked;

        public :
            Element(sf::Vector2f &position, float angle, std::string& file, b2World& world);
            ~Element();
            void clic(sf::Sprite& mouse);
            void rotate(int value);
            bool test(float value);
            void render(sf::RenderWindow* window, const sf::Input& input);
    };
#endif
