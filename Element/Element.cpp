#include "Element.h"
#include <iostream>

/* modified by Vincent */

Element::Element(sf::Vector2f& position, float angle, std::string& file, b2World& world) : clicked(false) {
    _image.LoadFromFile("ressources/images/" + file);
    _sprite.SetImage(_image);
    _sprite.SetPosition(position);
    _sprite.SetRotation(angle);
    _sprite.SetCenter(_image.GetWidth()/2, _image.GetHeight()/2);

    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(position.x, position.y);
    bd.angle = Collision::to_radian(angle);
    _body = world.CreateBody(&bd);

    b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(_image.GetWidth() / 2.0f, _image.GetHeight() / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 100.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.3f;
    _body->CreateFixture(&fixtureDef);
}

Element::~Element() {
    Logger::Instance()->log("Element détruit");
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

