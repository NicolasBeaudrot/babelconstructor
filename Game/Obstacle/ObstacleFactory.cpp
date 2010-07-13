#include "ObstacleFactory.h"

ObstacleFactory::ObstacleFactory() {
}

ObstacleFactory::~ObstacleFactory() {
}

void ObstacleFactory::Init(sf::RenderWindow *application, b2World *world) {
    _world = world;
    _app   = application;
}

void ObstacleFactory::Delete() {
    for (unsigned int i = 0; i < _tabObst.size(); i++) {
        delete _tabObst[i];
    }
    _tabObst.clear();
}

void ObstacleFactory::add(std::string type, sf::Vector2f& position, float& angle, std::string file, sf::Vector2f& base_position) {
    position.x = base_position.x + position.x;
    position.y = base_position.y - position.y;

    if (type == "Square" or type == "Rectangle") {
        SquareObstacle *elem = new SquareObstacle(position, angle, file, *_world, _app);
        _tabObst.push_back(elem);
    }
}

void ObstacleFactory::render() {
    for (unsigned int i = 0; i < _tabObst.size(); i++) {
        _tabObst[i]->render();
    }
}
