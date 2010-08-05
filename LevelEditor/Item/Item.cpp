#include "Item.h"

Item::Item(QString file, int type, int id) : _item(type), _id(id) {
    _image.LoadFromFile(file.toStdString());
    _sprite.SetImage(_image);
    _sprite.SetCenter(_sprite.GetSize() / 2.0f);
    _isVisible = true;
    _type = "Square";
    QStringList files = file.split('/');
    _texture = files.last();
    _properties[0] = _image.GetWidth();
    _properties[1] = _image.GetHeight();
    for(int i=2; i < 8; i++) {
        _properties[i] = 0.0f;
    }
    _properties[5] = 100.0f;
}

void Item::setVisibility(bool visible) {
    _isVisible = visible;
}

void Item::setPosition(sf::Vector2f position) {
    _isVisible = true;
    _properties[2] = position.x;
    _properties[3] = position.y;
    _sprite.SetPosition(position.x, position.y);
}

void Item::setProperties(float *prop) {
    for(int i=5; i < 8; i++) {
        _properties[i] = prop[i];
    }
    _sprite.SetPosition(_properties[2] - _image.GetWidth()/2, _properties[3] - _image.GetHeight()/2);
    _sprite.SetRotation(_properties[4]);
}

void Item::setProperty(int index, float prop) {
    _properties[index] = prop;
}

void Item::setType(QString type) {
    _type = type;
}

void Item::setRotation(float value) {
    _sprite.SetRotation(value);
    _properties[4] = value;
}

void Item::move(int value, int direction) {
    if (direction == 0) { //Horizontale
        _properties[2] = _sprite.GetPosition().x + value;
        _sprite.SetX(_properties[2]);
    } else { //Verticale
        _properties[3] = _sprite.GetPosition().y + value;
        _sprite.SetY(_properties[3]);
    }
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

int Item::getItemType() {
    if(_isVisible) {
        return _item;
    } else {
        return 0;
    }
}

float* Item::getProperties() {
    return _properties;
}

QString Item::getTexture() {
    return _texture;
}

QString Item::getType() {
    return _type;
}

void Item::render(QSFMLCanvas &win) {
    if (_isVisible) {
        win.Draw(_sprite);
    }
}
