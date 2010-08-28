#include "GameManager.h"
#include <tinyxml.h>
#include <tinyxml.cpp>
#include <tinyxmlerror.cpp>
#include <tinyxmlparser.cpp>
#include <tinystr.cpp>
#include <tinystr.h>
#include <sstream>

GameManager::GameManager() {
}

GameManager::~GameManager() {
    _app.Close();
}

void GameManager::Init() {
    TiXmlDocument doc("ressources/config.xml");
    int width, height, colors;
    std::string fullscreen = "false";
    _paused = 1;
    _winner = false;
    width = 800;
    height = 600;
    colors = 32;

    if (!doc.LoadFile()) {
        Logger::Instance()->log("Unable to load the config file");
    } else {
        Logger::Instance()->log("Config loaded");
        TiXmlHandle hdl(&doc);
        TiXmlElement *win;
        win = hdl.FirstChildElement("game").FirstChild("window").Element();
        fullscreen = win->Attribute("fullscreen");
    }
    if (fullscreen == "true") {
        _app.Create(sf::VideoMode(width, height, colors), "Babel Constructor", sf::Style::Fullscreen);
    } else {
        _app.Create(sf::VideoMode(width, height, colors), "Babel Constructor", sf::Style::Close);
    }
    _app.SetFramerateLimit(60);
}


sf::RenderWindow &GameManager::getApp() {
    return _app;
}

void GameManager::run(std::string path) {

    loadMap(path);
    sf::Font *font = RessourceManager::Instance()->GetFont("ressources/fonts/gilligan.ttf");
    sf::String str_counter;
    str_counter.SetPosition(_app.GetWidth()-50, 20);
    str_counter.SetFont(*font);
    str_counter.SetSize(25);
    bool open = true;

    while (open) {
        sf::Event Event;
        while (_app.GetEvent(Event))  {
            if (Event.Type == sf::Event::Closed || (Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::Escape)) {
                open = false;
            } else if (Event.Type == sf::Event::MouseButtonReleased && !_winner && _paused == 1) {
                ElementFactory::Instance()->clic(_app.GetInput());
            } else if (Event.Type == sf::Event::KeyPressed && (Event.Key.Code == sf::Key::Up || Event.Key.Code == sf::Key::Down)) {
                if (Event.Key.Code == sf::Key::Up) {
                    ElementFactory::Instance()->rotate(0.1);
                } else {
                    ElementFactory::Instance()->rotate(-0.1);
                }
            } else if (Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::N && !MapManager::Instance()->isOfficialMode()) {
                destroyWorld();
                loadMap();
            } else if (Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::P) {
                if (_paused == 0) {
                    _paused = 1;
                } else {
                    _paused = 0;
                }
            } else if (Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::Return) {
                destroyWorld();
                loadMap(MapManager::Instance()->getCurrentMapName());
            }else if(Event.Type == sf::Event::MouseMoved){
                ElementFactory::Instance()->move(_app.GetInput());
            }
        }

        _app.Clear(sf::Color::Black);

        if (_paused == 1) {
            _counter.Start();
            world->Step(_app.GetFrameTime(), 6, 2);
            std::ostringstream oss;
            oss << floor(_counter.GetElapsedTime());
            str_counter.SetText(oss.str());
        } else {
            _counter.Pause();
        }

        int status = ElementFactory::Instance()->render(_app.GetInput());

        //Pause
        if (_paused == 0) {
            sf::String pause("Paused", *font, 50);
            pause.SetPosition(_app.GetWidth()/2-100, 100);
            _app.Draw(pause);
        }

        //Intro
        if (_intro.GetElapsedTime() < 5.0f) {
            sf::String intro("Map : " + MapManager::Instance()->getCurrentMapName(), *font, 20);
            intro.SetPosition(10, 10);
            _app.Draw(intro);
        }

        _app.Draw(str_counter);

        //Winner
        if (status != 0) {
            if(status == 1) {
                sf::String text("Winner", *font, 50);
                text.SetPosition(_app.GetWidth()/2-50, 10);
                _app.Draw(text);
                if (_first_loop) {
                    _winner = true;
                    _paused = 2;
                    ScoreManager::Instance()->update(MapManager::Instance()->getCurrentMapName(), _counter.GetElapsedTime());
                    ScoreManager::Instance()->save("ressources/config.xml");
                    _first_loop = false;
                }
            } else if (status == 2) {
                destroyWorld();
                loadMap();
            }
        } else { //Loser
            if(ElementFactory::Instance()->below() && !_winner) {
                sf::String perdu("You lose !", *font, 50);
                perdu.SetPosition(_app.GetWidth()/2-100, 10);
                _app.Draw(perdu);
                _paused = 2;
            }
        }

        _app.SetView(_app.GetDefaultView());
        _app.Display();
    }
    destroyWorld();
    MapManager::Instance()->stop();
}


void GameManager::createWorld() {
    b2Vec2 gravity(0.0f, -170.0f);
	world = new b2World(gravity, true);

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

void GameManager::loadMap(std::string path) {
    _intro.Reset();
    _counter.Reset();
    _winner = false;
    _first_loop = true;
    _paused = 1;
    createWorld();
    ElementFactory::Instance()->Init(& _app,world );
    ObstacleFactory::Instance()->Init(&_app, world);

    if ( path.empty() ) {
        MapManager::Instance()->nextMap();
    } else {
        MapManager::Instance()->load(path);
    }
}
