#include "Element.h"
#include "ElementFactory.h"

Element::Element() : clicked(false) {
}

Element::~Element() {
    Logger::Instance()->log("Element deleted");
}

float Element::getYPosition() {
    b2Vec2 pos = _body->GetPosition();
    b2Transform t = _body->GetTransform();
    float height;

    if ((t.R.col1.y >= 0.8 && t.R.col1.y <= 1) || (t.R.col1.y >= -1 && t.R.col1.y <= -0.8)) { //La forme est debout
        height = _image->GetWidth()/2;
    } else { //La forme est normale
        height = _image->GetHeight()/2;
    }
    return ((_app->GetHeight() - pos.y) -  height);
}

void Element::clic(b2Body * body) {
    //We compare the bodies to know if this Element is selected or not
    if (!clicked && _body == body ) {
        clicked = true;
    } else {
        clicked = false;
    }
}

void Element::rotate(float value) {
    if (clicked) {
        _body->SetTransform(_body->GetPosition(), _body->GetAngle()+ value);
    }
}

bool Element::test(float value) {
    if (!clicked) {
        if (getYPosition() <= value) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool Element::below(float value) {
    b2Vec2 pos = _body->GetPosition();

    if (((_app->GetHeight() - pos.y) - _image->GetHeight()/2) >= value) {
        return true;
    } else {
        return false;
    }
}

void Element::render(const sf::Input& input) {

    b2Vec2 position = _body->GetPosition();
    _sprite.SetX(_app->GetWidth() - position.x);
    _sprite.SetY(_app->GetHeight() - position.y);
    _sprite.SetRotation(-Conversion::to_degres(_body->GetAngle()));

    _app->Draw(_sprite);
}

