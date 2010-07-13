#include "SquareObstacle.h"

SquareObstacle::SquareObstacle(sf::Vector2f& position, float& angle, std::string file, b2World& world, sf::RenderWindow *application) : Obstacle() {
    _app = application;
    std::string path = "ressources/images/" + file;

    _image = RessourceManager::Instance()->GetImage(path);
    _sprite.SetImage(*_image);
    _sprite.SetPosition(position);
    _sprite.SetCenter(_image->GetWidth()/2, _image->GetHeight()/2);
    _sprite.SetRotation(angle);

    b2BodyDef obsBodyDef;
	obsBodyDef.position.Set(application->GetWidth() - position.x, application->GetHeight() - position.y);
	obsBodyDef.angle = -Collision::to_radian(angle);
	b2Body* obsBody = world.CreateBody(&obsBodyDef);
	b2PolygonShape obsBox;
    obsBox.SetAsBox(_image->GetWidth()/2.0f, _image->GetHeight()/2.0f);
	obsBody->CreateFixture(&obsBox, 0.0f);

    Logger::Instance()->log("SquareObstacle loaded");
}
