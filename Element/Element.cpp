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
    std::cout << _sprite.GetPosition().y << std::endl;
    return (_sprite.GetPosition().y <= value);
}


void Element::render(sf::RenderWindow* window, const sf::Input& input) {
    if (clicked) {
        _sprite.SetX(input.GetMouseX());
        _sprite.SetY(input.GetMouseY());
        b2Vec2 position(window->GetWidth() - input.GetMouseX(),window->GetHeight() - input.GetMouseY());
        _body->SetTransform(position, Collision::to_radian(-_sprite.GetRotation()));
    } else {
        b2Vec2 position = _body->GetPosition();
        _sprite.SetX(window->GetWidth() - position.x);
        _sprite.SetY(window->GetHeight() - position.y);
        _sprite.SetRotation(-Collision::to_degres(_body->GetAngle()));
    }

    window->Draw(_sprite);
}

