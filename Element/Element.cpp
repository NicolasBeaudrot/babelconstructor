#include "Element.h"
#include <iostream>

Element::Element() : clicked(false),xClicked(NULL),yClicked(NULL) {
}

Element::~Element() {
    Logger::Instance()->log("Element destroyed");
}

void Element::clic(sf::Sprite& mouse) {
    if (!clicked && Collision::PixelPerfectTest(_sprite, mouse)) {
        clicked = true;
       // _body->SetActive(true);
    } else {
        clicked = false;
       // _body->SetActive(true);
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

        //1er clic
        if(!xClicked && !yClicked){
            xClicked=input.GetMouseX();
            yClicked=input.GetMouseY();

        }

        int deltaX = input.GetMouseX() - xClicked;
        int deltaY = input.GetMouseY() - yClicked;

        _sprite.SetX(_sprite.GetPosition().x + deltaX );
        _sprite.SetY(_sprite.GetPosition().y + deltaY);

        b2Vec2 position(_app->GetWidth() - _sprite.GetPosition().x, _app->GetHeight() - _sprite.GetPosition().y);
        _body->SetTransform(position, Collision::to_radian(-_sprite.GetRotation()));

        //maj
        xClicked=input.GetMouseX();
        yClicked=input.GetMouseY();

    } else {
        xClicked=NULL;
        yClicked=NULL;
        b2Vec2 position = _body->GetPosition();
        _sprite.SetX(_app->GetWidth() - position.x);
        _sprite.SetY(_app->GetHeight() - position.y);
        _sprite.SetRotation(-Collision::to_degres(_body->GetAngle()));
    }

    _app->Draw(_sprite);
}

