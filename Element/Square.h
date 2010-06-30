#ifndef SQUARE_H
#define SQUARE_H
#include "Element.h"

    class Square : public Element
    {

        public :
            Square(sf::Vector2f &position, float angle, std::string& file, b2World& world, float* fixture, sf::RenderWindow *application);
            ~Square();
    };

#endif
