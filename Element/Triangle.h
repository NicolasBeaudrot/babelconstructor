#ifndef TRIANGLE_H
#define TRIANGLE_H
#include  "Element.h"

    class Triangle : public Element
    {
        public :
            Triangle(sf::Vector2f &position, float angle, std::string& file, b2World& world, float* fixture, sf::RenderWindow *application);
    };

#endif
