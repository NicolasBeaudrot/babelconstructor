#ifndef ELEMENT_H
#define ELEMENT_H
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Utility/Collision.h"
#include "../Utility/Logger.h"
#include "../Utility/ImageManager.h"
#include <Box2D/Box2D.h>

    class Element
    {
        protected :
            b2Body* _body;
            bool clicked;
            sf::Image *_image;
            sf::Sprite _sprite;
            sf::RenderWindow *_app;

            int xClicked;
            int yClicked;

        public :
            Element();
            ~Element();
            void clic(sf::Sprite& mouse);
            void rotate(int value);
            bool test(float value);
            void render(const sf::Input& input);
    };
#endif
