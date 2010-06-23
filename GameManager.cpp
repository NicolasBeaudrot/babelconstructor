#include "GameManager.h"


GameManager::GameManager() : _app(), _camera(), current_map("map1.xml"){
    _app.Create(sf::VideoMode(800, 600, 32), "Babel Constructor");

    MapManager::Instance()->Init(&_app, &_camera);
    ElementFactory::Instance()->Init(&_app);
    Logger::Instance()->Init();
}

GameManager::~GameManager() {
    destroyWorld();
    delete MapManager::Instance()->getCurrentMap;
    MapManager::Kill();
    ElementFactory::Kill();
    Logger::Kill();
}

void GameManager::createWorld() {
    b2Vec2 gravity(0.0f, -170.0f);
	bool doSleep = true;
	world = new b2World(gravity, doSleep);

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, 0.0f);
	b2Body* groundBody = world->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(_app.GetWidth(), 0.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);
}

void GameManager::destroyWorld() {
    b2Body* node = world->GetBodyList();
    while (node) {
        b2Body* b = node;
        node = node->GetNext();
        world->DestroyBody(b);
        node = world->GetBodyList();
    }

    delete world;
}

void GameManager::run() {

    createWorld();
    MapManager::Instance()->Load(current_map, *world);

    while (_app.IsOpened()) {
        sf::Event Event;
        while (_app.GetEvent(Event))  {
            if (Event.Type == sf::Event::Closed) {
                _app.Close();
            } else if (Event.Type == sf::Event::MouseButtonReleased) {
                ElementFactory::Instance()->clic(_app.GetInput());
            } else if (Event.Type == sf::Event::KeyPressed
                       && (Event.Key.Code == sf::Key::Up || Event.Key.Code == sf::Key::Down)) {
                if (Event.Key.Code == sf::Key::Up) {
                    ElementFactory::Instance()->rotate(4);
                } else {
                    ElementFactory::Instance()->rotate(-4);
                }
            } else if (Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::N) {
                destroyWorld();
                delete MapManager::Instance()->getCurrentMap;
                createWorld();
                MapManager::Instance()->Load("map2.xml", *world);
            }
        }

        _app.SetFramerateLimit(100);

        _app.Clear();

        world->Step(_app.GetFrameTime(), 6, 2);

        MapManager::Instance()->getCurrentMap->render(_app.GetInput());

		_app.SetView(_app.GetDefaultView());
        _app.Display();
    }
}
