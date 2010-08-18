#ifndef WIDGET_H
#define WIDGET_H
#include <string>
#include "../GameManager.h"

    class Widget
    {
        protected :
            std::string _name;
            bool _visible;
            GameManager* _game;
            std::vector<sf::Image*> _arrImages;
            std::vector<sf::Sprite> _arrSprites;

        public :
            Widget(GameManager* game, std::string name);
            virtual ~Widget();
            virtual bool intersect(float x, float y) = 0;
            virtual void onClic(int bouton) = 0;
            virtual void onHover() = 0;
            virtual void setPosition(float x, float y) = 0;
            virtual void display(sf::RenderWindow* app) = 0;

            std::string getName();
            bool getVisibility();
            void setName(std::string name);
            void setVisibility(bool visible);
            void addTexture(std::string path);

    };

#endif
