#ifndef ITEM_H
#define ITEM_H
#include <QString>
#include <SFML/Graphics.hpp>
#include "Canvas/QSFMLCanvas.hpp"

    class Item
    {
        private :
            sf::Image _image;
            sf::Sprite _sprite;
            bool _isVisible;
            int _type;
            int _id;

        public :
            Item(QString file, int type, int id);

            void setPosition(sf::Vector2f position);

            bool isClicked(float x, float y);

            int getType();

            void render(QSFMLCanvas &win);
    };

#endif // ITEM_H
