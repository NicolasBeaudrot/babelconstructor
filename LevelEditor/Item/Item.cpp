#include "Item.h"

Item::Item(QString file, int type, int id) : _type(type), _id(id) {
    _image.LoadFromFile(file.toStdString());
    _sprite.SetImage(_image);
    _isVisible = true;
}

void Item::setPosition(sf::Vector2f position) {
    _isVisible = true;
    _sprite.SetPosition(position.x - _image.GetWidth()/2, position.y - _image.GetHeight());
}

void Item::render(QSFMLCanvas &win) {
    if (_isVisible) {
        win.Draw(_sprite);
    }
}
