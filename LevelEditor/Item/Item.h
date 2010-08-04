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
            QString _type;
            bool _isVisible;
            int _item;
            int _id;
            float _properties[8]; //0:Width, 1:Height, 2:X, 3:Y, 4:Angle, 5:Density, 6:Restitution, 7:Friction

        public :
            Item(QString file, int type, int id);

            void setPosition(sf::Vector2f position);

            void setProperties(float *prop);

            void setProperties(int index, float prop);

            void setRotation(float value);

            void setType(QString type);

            void setVisibility(bool visible);

            void move(int value, int direction);

            int getItemType();

            float* getProperties();

            QString getTexture();

            QString getType();

            bool isClicked(float x, float y);

            void render(QSFMLCanvas &win);
    };

#endif // ITEM_H
