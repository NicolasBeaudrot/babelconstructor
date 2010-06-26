#include "Square.h"

Square::Square(sf::Vector2f &position, float angle, std::string& file, b2World& world, float* fixture) : Element() {
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
	fixtureDef.density = fixture[0];
	fixtureDef.friction = fixture[1];
	fixtureDef.restitution = fixture[2];
    _body->CreateFixture(&fixtureDef);

    Logger::Instance()->log("Square loaded");
}
