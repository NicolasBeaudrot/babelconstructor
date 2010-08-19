#include "Triangle.h"

Triangle::Triangle(sf::Vector2f &position, float angle, std::string& file, b2World& world, float* fixture, sf::RenderWindow *application) : Element() {
    _app = application;
     std::string path = "ressources/images/elements/" + file;
    _image = RessourceManager::Instance()->GetImage(path);
    position.x += (_image->GetWidth()/2);
    position.y += (_image->GetHeight()/2);
    _sprite.SetImage(*_image);
    _sprite.SetRotation(angle);
    _sprite.SetCenter(_image->GetWidth()/2, _image->GetHeight()/2);
    _sprite.SetPosition(position);

    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(_app->GetWidth() - position.x, _app->GetHeight() - position.y);
    bd.angle = -Conversion::to_radian(angle);
    bd.angularDamping = 0.01f;
    _body = world.CreateBody(&bd);

	b2Vec2 vertices[3];
	float width = _image->GetWidth()/2;
	float heigth = _image->GetHeight()/2;

	vertices[1].Set(-width, -heigth);
    vertices[2].Set(width, -heigth);
    vertices[0].Set(0.0f, heigth);
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
