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

    createWorld();
    MapManager::Instance()->Init(&_app, &_camera);
    ElementFactory::Instance()->Init(&_app, world);
    ObstacleFactory::Instance()->Init(&_app, world);
    Logger::Instance()->Init();
}

GameManager::~GameManager() {
    destroyWorld();
    MapManager::Kill();
    ElementFactory::Kill();
    ObstacleFactory::Kill();
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

    MapManager::Instance()->nextMap();
    bool paused = false;
    bool winner = false;

    while (_app.IsOpened()) {
        sf::Event Event;
        while (_app.GetEvent(Event))  {
            if (Event.Type == sf::Event::Closed || (Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::Escape)) {
                _app.Close();
            } else if (Event.Type == sf::Event::MouseButtonReleased && !winner) {
                ElementFactory::Instance()->clic(_app.GetInput());
            } else if (Event.Type == sf::Event::KeyPressed && (Event.Key.Code == sf::Key::Up || Event.Key.Code == sf::Key::Down)) {
                if (Event.Key.Code == sf::Key::Up) {
                    ElementFactory::Instance()->rotate(0.1);
                } else {
                    ElementFactory::Instance()->rotate(-0.1);
                }
            } else if (Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::N) {
                destroyWorld();
                createWorld();
                ElementFactory::Instance()->Init(& _app,world );
                ObstacleFactory::Instance()->Init(&_app, world);
                MapManager::Instance()->nextMap();
            } else if (Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::P) {
                paused = !paused;
            } else if (Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::Return) {
                paused = false;
                destroyWorld();
                createWorld();
                ElementFactory::Instance()->Init(& _app,world );
                ObstacleFactory::Instance()->Init(&_app, world);
                MapManager::Instance()->reLoad();

            }else if(Event.Type == sf::Event::MouseMoved){
                ElementFactory::Instance()->move(_app.GetInput());
            }
        }

        if (!paused) {
            _app.SetFramerateLimit(100);
            _app.Clear();

            world->Step(_app.GetFrameTime(), 6, 2);

            //Winner
            int status = ElementFactory::Instance()->render(_app.GetInput());
            if (status != 0) {
                if(status == 1) {
                    sf::Font *font   = RessourceManager::Instance()->GetFont("ressources/fonts/gilligan.ttf");
                    sf::String text("Winner", *font, 50);
                    text.SetPosition(_app.GetWidth()/2-50, 10);
                    _app.Draw(text);
                    winner = true;
                } else if (status == 2) {
                    destroyWorld();
                    createWorld();
                    MapManager::Instance()->nextMap();
                }
            } else {
                //Loser
                if(ElementFactory::Instance()->below()) {
                    sf::Font *font   = RessourceManager::Instance()->GetFont("ressources/fonts/gilligan.ttf");
                    sf::String perdu("You lose !", *font, 50);
                    perdu.SetPosition(_app.GetWidth()/2-100, 10);
                    _app.Draw(perdu);
                    paused = true;
                }
            }

            _app.SetView(_app.GetDefaultView());
            _app.Display();
        }
    }
}
