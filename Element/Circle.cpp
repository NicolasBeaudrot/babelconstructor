#include "Circle.h"

Circle::Circle(sf::Vector2f &position, float angle, std::string& file, b2World& world, float* fixture, sf::RenderWindow *application) : Element() {
    _app = application;
    std::string path = "ressources/images/" + file;
    _image = ImageManager::Instance()->GetImage(path);
    _sprite.SetImage(*_image);
    _sprite.SetPosition(position);
    _sprite.SetRotation(angle);
    _sprite.SetCenter(_image->GetWidth()/2, _image->GetHeight()/2);

    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(_app->GetWidth() - position.x, _app->GetHeight() - position.y);
    bd.angle = -Collision::to_radian(angle);
    _body = world.CreateBody(&bd);

    b2CircleShape circle;
    circle.m_p.Set(_image->GetWidth()*0.000264583, _image->GetWidth()*0.000264583);
    circle.m_radius = _image->GetWidth()/2;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.density = fixture[0];
	fixtureDef.friction = fixture[1];
	fixtureDef.restitution = fixture[2];
    _body->CreateFixture(&fixtureDef);

    Logger::Instance()->log("Circle loaded");
}
