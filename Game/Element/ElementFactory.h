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
#ifndef ELEMENTFACTORY_H
#define ELEMENTFACTORY_H
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Utility/Singleton.h"
#include "../Utility/Logger.h"
#include <vector>
#include "Element.h"
#include "Square.h"
#include "Circle.h"
#include "Triangle.h"

    class ElementFactory : public CSingleton<ElementFactory>, public b2ContactListener
    {
        private :
            friend class CSingleton<ElementFactory>;
            ElementFactory();
            virtual ~ElementFactory();
            std::vector<Element*> _tabElem;
            bool clicked, tested;
            b2World *_world;
            b2MouseJoint* _mouseJoint;
            b2Body* _groundBody;
            sf::Font *_font;
            sf::Clock _clock;
            sf::RenderWindow *_app;
            sf::Sprite _mouse;
            sf::Image _img_back;
            sf::Sprite _sprite_back;
            sf::Image _img_base;
            sf::Sprite _sprite_base;
            sf::Image _img_limite;
            sf::Sprite _sprite_limite;

        public :
            /**
            * Constructor
            * @param : SFML window
            */
            void Init(sf::RenderWindow *application,b2World *);

            /**
            * Destructor
            */
            void Delete();

            /**
            * This function is used to load the background, the base and the limit
            * @param background : background texture filename
            * @param base : base texture filename
            * @param dimension : width and height of the base
            * @param world : box2D world
            * @param limite : limit texture filename
            * @param limite_y : y position of the limit
            */
            void loadBase(std::string background, std::string base, sf::Vector2f& dimension, b2World& world, std::string limite, float limite_y);

            /**
            * This function is used to load an element
            * @param type : shape type
            * @param position : initial position
            * @param angle : initial angle
            * @param file : texture filename
            * @param world : box2D object
            * @param fixture : an array containing physical informations
            */
            void add(std::string type, sf::Vector2f& position, float& angle, std::string file, b2World& world, float* fixture);

            /**
            * This function is used to call each element when there is a mouse clic
            * @param input : mouse coordonnates
            */
            void clic(const sf::Input& input);

            /**
            * This function is called when the mouse is moved
            * @param input : mouse coordonnates
            */
            void move(const sf::Input& input);

            /**
            * This function is used to call each element to know if one is below the base position
            */
            bool below();

            /**
            * This function is used to call each element when there is a rotation
            * @param value : angle value added
            */
            void rotate(const int value);

            /**
            * This function is used to call each element for rendering and to konw if one is upper than the limit
            * @param input contains mouse coordonates
            * @return true if the map is over else false
            */
            bool render(const sf::Input& input);

            virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
            virtual void BeginContact(b2Contact* contact) { B2_NOT_USED(contact); }
            virtual void EndContact(b2Contact* contact) { B2_NOT_USED(contact); }
            virtual void PostSolve(const b2Contact* contact, const b2ContactImpulse* impulse)
            {
                B2_NOT_USED(contact);
                B2_NOT_USED(impulse);
            }


    };

#endif
