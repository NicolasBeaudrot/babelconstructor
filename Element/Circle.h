#ifndef CIRCLE_H
#define CIRCLE_H
#include "Element.h"

    class Circle : public Element
    {
        public :
            Circle(sf::Vector2f &position, float angle, std::string& file, b2World& world, float* fixture);
    };

#endif
