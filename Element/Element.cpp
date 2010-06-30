#include "Element.h"
#include <iostream>

Element::Element() : clicked(false) {
}

Element::~Element() {
    Logger::Instance()->log("Element destroyed");
}

void Element::clic(sf::Sprite& mouse) {
    if (!clicked && Collision::PixelPerfectTest(_sprite, mouse)) {
        clicked = true;
        _body->SetActive(false);
    } else {
        clicked = false;
        _body->SetActive(true);
    }
}

void Element::rotate(int value) {
    if (clicked) {
        _sprite.Rotate(value);
    }
}

bool Element::test(float value) {
    b2Vec2 pos = _body->GetPosition();
    return (((_app->GetHeight() - pos.y) -  _image->GetHeight()/2) <= value);
}


void Element::render(const sf::Input& input) {
    if (clicked) {
        _sprite.SetX(input.GetMouseX());
        _sprite.SetY(input.GetMouseY());
        b2Vec2 position(_app->GetWidth() - input.GetMouseX(), _app->GetHeight() - input.GetMouseY());
        _body->SetTransform(position, Collision::to_radian(-_sprite.GetRotation()));
    } else {
        b2Vec2 position = _body->GetPosition();
        _sprite.SetX(_app->GetWidth() - position.x);
        _sprite.SetY(_app->GetHeight() - position.y);
        _sprite.SetRotation(-Collision::to_degres(_body->GetAngle()));
    }

    _app->Draw(_sprite);
}

