#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H
#include "Item.h"
#include "Canvas/QSFMLCanvas.hpp"
#include <vector>
#include <QString>

    class ItemFactory
    {
        private :
            std::vector<Item*> _itemsArray;
        public :
            ItemFactory();

            ~ItemFactory();

            int add(int type, QString file);

            void remove(int index);

            void setPosition(int index, sf::Vector2f position);

            void setProperties(int index, float *prop);

            void setRotation(int index, float value);

            void setType(int index, QString type);

            void move(int index, int value, int direction);

            int isClicked(float x, float y);

            QString save(float rep_x, float rep_y);

            int getItemType(int index);

            QString getType(int index);

            float* getProperties(int index);

            QString getTexture(int index);

            void render(QSFMLCanvas &win);
    };
#endif // ITEMFACTORY_H
