#include "Item.h"

Item::Item(QString file, int type, int id) : _type(type), _id(id) {
    _image.LoadFromFile(file.toStdString());
    _sprite.SetImage(_image);
    _sprite.SetCenter(_sprite.GetSize() / 2.0f);
    _isVisible = true;
}

void Item::setVisibility(bool visible) {
    _isVisible = visible;
}

void Item::setPosition(sf::Vector2f position) {
    _isVisible = true;
    _sprite.SetPosition(position.x - _image.GetWidth()/2, position.y - _image.GetHeight()/2);
}

bool Item::isClicked(float x, float y) {
    if (x >= (_sprite.GetPosition().x - _image.GetWidth()/2) && x <= (_sprite.GetPosition().x - _image.GetWidth()/2 + _image.GetWidth())
        && y >= (_sprite.GetPosition().y - _image.GetHeight()/2) && y <= (_sprite.GetPosition().y - _image.GetHeight()/2 + _image.GetHeight())
        && _isVisible) {
        return true;
    } else {
        return false;
    }
}

int Item::getType() {
    return _type;
}

void Item::render(QSFMLCanvas &win) {
    if (_isVisible) {
        win.Draw(_sprite);
    }
}
