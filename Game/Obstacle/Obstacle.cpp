#include "Obstacle.h"

Obstacle::Obstacle() {

}

Obstacle::~Obstacle() {
}

void Obstacle::render() {
    _app->Draw(_sprite);
}
