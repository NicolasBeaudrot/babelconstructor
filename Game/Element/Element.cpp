#include "Element.h"
#include "ElementFactory.h"

Element::Element() : clicked(false), xClicked(NULL), yClicked(NULL) {
}

Element::~Element() {
    Logger::Instance()->log("Element deleted");
}

void Element::clic(sf::Sprite& mouse,b2Body * body) {
    //if (!clicked && Collision::PixelPerfectTest(_sprite, mouse) ) {
    //We compare the bodies to know if this Element is selected or not
    if (!clicked && _body == body ) {
        clicked = true;
       // _body->SetActive(true);
    } else {
        clicked = false;
       // _body->SetActive(true);
    }
}

void Element::rotate(float value) {
    if (clicked) {
        _body->SetTransform(_body->GetPosition(), _body->GetAngle()+ value);
        //_sprite.Rotate(value);
    }
}

bool Element::test(float value) {
    if (!clicked) {
        b2Vec2 pos = _body->GetPosition();
        b2Transform t = _body->GetTransform();
        float height;
        if ((t.R.col1.y >= 0.8 && t.R.col1.y <= 1) || (t.R.col1.y >= -1 && t.R.col1.y <= -0.8)) { //La forme est debout
            height = _image->GetWidth()/2;
        } else { //La forme est normale
            height = _image->GetHeight()/2;
        }

        if (((_app->GetHeight() - pos.y) -  height) <= value) {
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
    //if (clicked) {

      /*  //1er clic
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
        yClicked=input.GetMouseY();*/

   // } else {
        xClicked=NULL;
        yClicked=NULL;
        b2Vec2 position = _body->GetPosition();
        _sprite.SetX(_app->GetWidth() - position.x);
        _sprite.SetY(_app->GetHeight() - position.y);
        _sprite.SetRotation(-Collision::to_degres(_body->GetAngle()));
   // }

    _app->Draw(_sprite);
}

