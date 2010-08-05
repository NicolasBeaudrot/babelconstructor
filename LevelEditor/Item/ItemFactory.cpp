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

void ItemFactory::setProperties(int index, float *prop) {
    _itemsArray[index]->setProperties(prop);
}

void ItemFactory::setProperty(int index, int prop, float value) {
    _itemsArray[index]->setProperty(prop, value);
}

void ItemFactory::setRotation(int index, float value) {
    _itemsArray[index]->setRotation(value);
}

void ItemFactory::setType(int index, QString type) {
    _itemsArray[index]->setType(type);
}

void ItemFactory::move(int index, int value, int direction) {
    _itemsArray[index]->move(value, direction);
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

QString ItemFactory::save(float rep_x, float rep_y) {
    QString xml;

    //Elements
    xml = "<elements>";
    for(unsigned int i=0; i < _itemsArray.size(); i++) {
        if(_itemsArray[i]->getItemType() == 2) {
            float *prop = _itemsArray[i]->getProperties();
            QString temp;
            xml += "<elem type=\"" + _itemsArray[i]->getType();
            xml += "\" file=\"" + _itemsArray[i]->getTexture() + "\" x=\"" + temp.setNum(prop[2] - (prop[0]/2) - rep_x);
            xml += "\" y=\"" + temp.setNum(rep_y - prop[3] + (prop[1]/2));
            xml += "\" angle=\"" + temp.setNum(prop[4]);
            xml += "\" density=\"" + temp.setNum(prop[5]);
            xml += "\" friction=\"" + temp.setNum(prop[6]);
            xml += "\" restitution=\"" + temp.setNum(prop[7]) + "\" />";
        }
    }
    xml += "</elements>";

    //Obstacles
    xml += "<obstacles>";
    for(unsigned int i=0; i < _itemsArray.size(); i++) {
        if(_itemsArray[i]->getItemType() == 3) {
            float *prop = _itemsArray[i]->getProperties();
            QString temp;
            xml += "<obstacle type=\"" + _itemsArray[i]->getType();
            xml += "\" file=\"" + _itemsArray[i]->getTexture() + "\" x=\"" + temp.setNum(prop[2] - rep_x);
            xml += "\" y=\"" + temp.setNum(rep_y - prop[3]);
            xml += "\" angle=\"" + temp.setNum(prop[4]) + "\" />";
        }
    }
    xml += "</obstacles>";

    return xml;
}

int ItemFactory::getItemType(int index) {
    return _itemsArray[index]->getItemType();
}

QString ItemFactory::getType(int index) {
    return _itemsArray[index]->getType();
}

float* ItemFactory::getProperties(int index) {
    return _itemsArray[index]->getProperties();
}

QString ItemFactory::getTexture(int index) {
    return _itemsArray[index]->getTexture();
}

void ItemFactory::render(QSFMLCanvas &win) {
    for(unsigned int i=0; i < _itemsArray.size() ; i++) {
        _itemsArray[i]->render(win);
    }
}

void ItemFactory::reset() {
    for(unsigned int i=0; i < _itemsArray.size(); i++) {
        delete _itemsArray[i];
    }
    _itemsArray.clear();
}
