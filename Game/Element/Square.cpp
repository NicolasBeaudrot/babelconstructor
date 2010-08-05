#include "Square.h"

Square::Square(sf::Vector2f &position, float angle, std::string& file, b2World& world, float* fixture, sf::RenderWindow *application) : Element() {
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
    bd.angle = -Collision::to_radian(angle);
    bd.angularDamping = 0.01f;
    _body = world.CreateBody(&bd);

    b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(_image->GetWidth() / 2.0f, _image->GetHeight() / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = fixture[0];
	fixtureDef.friction = fixture[1];
	fixtureDef.restitution = fixture[2];
    _body->CreateFixture(&fixtureDef);

    Logger::Instance()->log("Square loaded");
}
