#ifndef ITEM_H
#define ITEM_H
#include <QString>
#include <SFML/Graphics.hpp>
#include "Canvas/QSFMLCanvas.hpp"
#include <iostream>

    class Item
    {
        private :
            sf::Image _image;
            sf::Sprite _sprite;
            QString _texture;
            bool _isVisible;
            int _type;
            int _id;
            float _properties[8];

        public :
            Item(QString file, int type, int id);

            void setPosition(sf::Vector2f position);

            void setVisibility(bool visible);

            int getType();

            float* getProperties();

            bool isClicked(float x, float y);

            void render(QSFMLCanvas &win);
    };

#endif // ITEM_H
