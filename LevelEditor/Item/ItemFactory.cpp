#include "ItemFactory.h"

ItemFactory::ItemFactory() {
}

ItemFactory::~ItemFactory() {
    for(unsigned int i=0; i < _itemsArray.size(); i++) {
        delete _itemsArray[i];
    }
}

int ItemFactory::add(int type, QString file) {
    Item *temp = new Item(file, type, _itemsArray.size());
    _itemsArray.push_back(temp);
    return (_itemsArray.size() - 1);
}

void ItemFactory::setPosition(int index, sf::Vector2f position) {
    _itemsArray[index]->setPosition(position);
}

void ItemFactory::render(QSFMLCanvas &win) {
    for(unsigned int i=0; i < _itemsArray.size() ; i++) {
        _itemsArray[i]->render(win);
    }
}
