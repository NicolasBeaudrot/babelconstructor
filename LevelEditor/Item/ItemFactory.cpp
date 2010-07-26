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

void ItemFactory::remove(int index) {
    _itemsArray[index]->setVisibility(false);
}

void ItemFactory::setPosition(int index, sf::Vector2f position) {
    _itemsArray[index]->setPosition(position);
}

int ItemFactory::isClicked(float x, float y) {
    int ret = -1;
    for( unsigned int i=0; i < _itemsArray.size(); i++) {
        if (_itemsArray[i]->isClicked(x,y)) {
            ret = i;
        }
    }
    return ret;
}

int ItemFactory::getType(int index) {
    return _itemsArray[index]->getType();
}

void ItemFactory::render(QSFMLCanvas &win) {
    for(unsigned int i=0; i < _itemsArray.size() ; i++) {
        _itemsArray[i]->render(win);
    }
}