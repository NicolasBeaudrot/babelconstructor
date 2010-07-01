#include "GameManager.h"
#include <tinyxml.h>
#include <tinyxml.cpp>
#include <tinyxmlerror.cpp>
#include <tinyxmlparser.cpp>
#include <tinystr.cpp>
#include <tinystr.h>

GameManager::GameManager() : _app(), _camera() {
    TiXmlDocument doc("ressources/config.xml");
    int width, height, colors;
    std::string fullscreen = "false";

    if (!doc.LoadFile()) {
        Logger::Instance()->log("Unable to load the config file");
        width = 800;
        height = 600;
        colors = 32;
    } else {
        Logger::Instance()->log("Config loaded");
        TiXmlHandle hdl(&doc);
        TiXmlElement *win;
        win = hdl.FirstChildElement("game").FirstChild("window").Element();
        win->QueryIntAttribute("width", &width);
        win->QueryIntAttribute("height", &height);
        win->QueryIntAttribute("colors", &colors);
        fullscreen = win->Attribute("fullscreen");
    }
    if (fullscreen == "true") {
        _app.Create(sf::VideoMode(width, height, colors), "Babel Constructor", sf::Style::Fullscreen);
    } else {
        _app.Create(sf::VideoMode(width, height, colors), "Babel Constructor");
    }

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
    RessourceManager::Kill();
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
    MapManager::Instance()->nextMap(*world);
    bool paused = false;

    while (_app.IsOpened()) {
        sf::Event Event;
        while (_app.GetEvent(Event))  {
            if (Event.Type == sf::Event::Closed
                        || (Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::Escape)) {
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
                createWorld();
                MapManager::Instance()->nextMap(*world);
            } else if (Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::P) {
                paused = !paused;
            }
        }

        if (!paused) {
            _app.SetFramerateLimit(100);
            _app.Clear();

            world->Step(_app.GetFrameTime(), 6, 2);

            if (ElementFactory::Instance()->render(_app.GetInput())) {
                destroyWorld();
                createWorld();
                MapManager::Instance()->nextMap(*world);
            }

            _app.SetView(_app.GetDefaultView());
            _app.Display();
        }
    }
}
