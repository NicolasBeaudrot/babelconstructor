#include "Element.h"
#include "ElementFactory.h"

Element::Element() : clicked(false), xClicked(NULL), yClicked(NULL), tested(false) {
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
        _clock.Reset();
       // _body->SetActive(true);
    }
}

void Element::rotate(int value) {
    if (clicked) {
        _sprite.Rotate(value);
    }
}

void Element::test(float value) {
    if (!clicked) {
        b2Vec2 pos = _body->GetPosition();
        if (((_app->GetHeight() - pos.y) -  _image->GetHeight()/2) <= value) {
            tested = true;
        } else {
            tested = false;
        }
    }
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

        if (tested) {
            if (_clock.GetElapsedTime() > 5) {
                sf::Font font;
                if (!font.LoadFromFile("ressources/fonts/gilligan.ttf", 50)) {
                    Logger::Instance()->log("Unable to load the font");
                }
                sf::String text("Winner", font, 50);
                text.SetPosition(_app->GetWidth()/2-50, 10);
                _app->Draw(text);
            }
        }
    }

    _app->Draw(_sprite);
}

