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

    class ElementFactory : public CSingleton<ElementFactory>
    {
        private :
            friend class CSingleton<ElementFactory>;
            ElementFactory();
            virtual ~ElementFactory();
            std::vector<Element*> _tabElem;
            sf::RenderWindow *_app;
            sf::Sprite _mouse;
            sf::Image _img_back;
            sf::Sprite _sprite_back;
            sf::Image _img_base;
            sf::Sprite _sprite_base;
            sf::Image _img_limite;
            sf::Sprite _sprite_limite;

        public :
            void Init(sf::RenderWindow *application);
            void Delete();
            void loadBase(std::string background, std::string base, sf::Vector2f& dimension, b2World& world, std::string limite, float limite_y);
            void add(std::string type, sf::Vector2f& position, float& angle, std::string file, b2World& world, float* fixture);
            void clic(const sf::Input& input);
            void rotate(int value);
            void render(const sf::Input& input);
    };

#endif
