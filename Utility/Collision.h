/*
 * File:   collision.h
 * Author: Nick Koirala
 *
 * Collision Detection and handling class
 * For SFML.

(c) 2009 - LittleMonkey Ltd

This software is provided 'as-is', without any express or
implied warranty. In no event will the authors be held
liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute
it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented;
   you must not claim that you wrote the original software.
   If you use this software in a product, an acknowledgment
   in the product documentation would be appreciated but
   is not required.

2. Altered source versions must be plainly marked as such,
   and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any
   source distribution.

 *
 * Created on 30 January 2009, 11:02
 */

#ifndef _COLLISION_H
#define	_COLLISION_H


#ifndef PI
    #define PI (3.14159265358979323846)
#endif
#define RADIANS_PER_DEGREE (PI/180.0)
#define ToRad(X) ( PI*(X)/180.f )        // Convertir des degrés en radian
#define ToDeg(X) ( 180.f*(X)/PI )        // Convertir des radians en degrés
#define Carre(X) ((X)*(X))                   // au carré
#include <cmath>

class Collision {
public:

    virtual ~Collision();

    /**
     *  Test for a pixel perfect collision detection between
     *  two Sprites, Rotation and Scale is supported in this test
     *
     *  @param Object1 The first sprite
     *  @param Object2 The second sprite
     *  @AlphaLimit How opaque a pixel needs to be before a hit it registered
     */
     static bool PixelPerfectTest(const sf::Sprite& Object1 ,const sf::Sprite& Object2, sf::Uint8 AlphaLimit = 127);

    /**
     *  Test for collision using circle collision dection
     *  Radius is averaged from the dimesnions of the sprite so
     *  roughly circular objects will be much more accurate
     */
    static bool CircleTest(const sf::Sprite& Object1, const sf::Sprite& Object2);

    /**
     *  Test for bounding box collision using OBB Box.
     *  To test against AABB use PixelPerfectTest with AlphaLimit = 0
     *
     *  @see Collision::PixelPerfectTest
     */
    static bool BoundingBoxTest(const sf::Sprite& Object1, const sf::Sprite& Object2);

    /**
     *  Generate a Axis-Aligned Bounding Box for broad phase of
     *  Pixel Perfect detection.
     *
     *  @returns IntRect to round off Floating point positions.
     */
    static sf::IntRect GetAABB(const sf::Sprite& Object);

    /**
     *  Helper function in order to rotate a point by an Angle
     *
     *  Rotation is CounterClockwise in order to match SFML Sprite Rotation
     *
     *  @param Point a Vector2f representing a coordinate
     *  @param Angle angle in degrees
     */
    static sf::Vector2f RotatePoint(const sf::Vector2f& Point, float Angle);

    /**
     *  Helper function to get the minimum from a list of values
     */
    static float MinValue(float a, float b, float c, float d);

    /**
     *  Helper function to get the maximum from a list of values
     */
    static float MaxValue(float a, float b, float c, float d);

    static float to_degres(float angle);

    static float to_radian(float angle);


    inline static float Distance(const float x1, const float y1, const float x2 = 0.f, const float y2 = 0.f)
    {
        return sqrt( (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) );
    }

    inline static float Distance(const sf::Vector2f& p1, const sf::Vector2f& p2 = sf::Vector2f(0.f, 0.f))
    {
        // Utilisation de l'autre fonction Distance.
        return Distance(p1.x, p1.y, p2.x, p2.y);
    }

    inline static sf::Vector2f Translate(const float distance, const float angle, const sf::Vector2f& p = sf::Vector2f(0.f, 0.f))
    {
        // X -1 en y car le repère est inversé dans SFML
        return sf::Vector2f(p.x + distance * std::cos(ToRad(angle)), p.y - distance * std::sin(ToRad(angle)));
    }

    inline static sf::Vector2f Translate(const sf::Vector2f& p, const sf::Vector2f& v)
    {
        return sf::Vector2f(p.x + v.x, p.y + v.y);
    }

    inline static float Angle(const float x1, const float y1, const float x2 = 0.f, const float y2 = 0.f)
    {
        float x = x1 - x2;
        float y = y1 - y2;

        if (y == 0.f)
        {
            if (x >= 0.f)
                return 0.f;
            else
                return 180.f;
        }

        if (y >= 0.f)
        {
            return ( ToDeg( std::atan(y/x) ) + 270.f );
        }
        else
        {
            return ( ToDeg( std::atan(y/x) ) + 90.f );
        }
    }

    inline static float Angle(const sf::Vector2f& p1, const sf::Vector2f& p2 = sf::Vector2f(0.f, 0.f))
    {
        return Angle(p1.x, p1.y, p2.x, p2.y);
    }

    inline static sf::Vector2f DansLeRepereDe(const sf::Drawable& Item, const sf::Vector2f& p)
    {
        float distance = Distance(p, Item.GetPosition());
        float angle = Angle(p, Item.GetPosition());

        return Translate(distance, angle - Item.GetRotation());
    }

    inline static bool IsPicked(const sf::Sprite& s, const sf::Vector2f& p, const int AlphaMax = -1)
    {

        sf::Vector2f pt = DansLeRepereDe(s, p) - s.GetCenter();

        if (
            pt.x > 0 &&
            pt.x < s.GetSize().x &&
            pt.y > 0 &&
            pt.y < s.GetSize().y
        )
        {
            if (AlphaMax >= 0)
            {
                if (s.GetPixel(static_cast<int>(pt.x), static_cast<int>(pt.y)).a <= AlphaMax)
                    return false;
            }

            return true;
        }

        return false;
    }

private:

    Collision();
};

#endif
