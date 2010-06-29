#include "Triangle.h"

Triangle::Triangle(sf::Vector2f &position, float angle, std::string& file, b2World& world, float* fixture) {
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

	b2Vec2 vertices[3];
    vertices[1].Set(-25.0f, -22.0f);
    vertices[2].Set(25.0f, -22.0f);
    vertices[0].Set(0.0f, 22.0f);
    int32 count = 3;

    b2PolygonShape triangle;
    triangle.Set(vertices, count);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &triangle;
	fixtureDef.density = fixture[0];
	fixtureDef.friction = fixture[1];
	fixtureDef.restitution = fixture[2];
    _body->CreateFixture(&fixtureDef);

    Logger::Instance()->log("Triangle loaded");
}
