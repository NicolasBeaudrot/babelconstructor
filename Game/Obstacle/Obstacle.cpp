#include "Obstacle.h"

Obstacle::Obstacle() {

}

Obstacle::~Obstacle() {
    Logger::Instance()->log("Obstacle deleted");
}

void Obstacle::render() {
    _app->Draw(_sprite);
}
