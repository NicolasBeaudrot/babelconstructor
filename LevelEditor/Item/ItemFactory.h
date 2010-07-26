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

            int isClicked(float x, float y);

            int getType(int index);

            void render(QSFMLCanvas &win);
    };
#endif // ITEMFACTORY_H