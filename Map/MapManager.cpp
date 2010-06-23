#include "MapManager.h"

MapManager::MapManager() :
                    _app(NULL),
                    _camera(NULL) {
    getCurrentMap = NULL;
}

MapManager::~MapManager() {
}

void MapManager::Init(sf::RenderWindow* windows, sf::View* camera) {
	_app = windows;
	_camera = camera;
}

void MapManager::Load(const std::string& nom, b2World& world) {
    getCurrentMap = new Map(_app, _camera, nom, world);
}

