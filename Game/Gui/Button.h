#ifndef BUTTON_H
#define BUTTON_H
#include "Widget.h"

    class Button : public Widget
    {
        private :
            bool _hover;
            std::string _action;
            sf::Font *_font;
            sf::String _name;

        public :
            Button(GameManager* game, std::string name, std::string texture, std::string action);
            bool intersect(float x, float y);
            void onClic(int bouton);
            void onHover();
            void setPosition(float x, float y);
            void display(sf::RenderWindow* app);
    };

#endif
