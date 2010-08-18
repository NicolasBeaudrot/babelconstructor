#include "GuiManager.h"
#include <sstream>

GuiManager::GuiManager(sf::RenderWindow* app, GameManager* game) {
    _app  = app;
    _game = game;
    _gui = new Gui(_app);
    init();
}

GuiManager::~GuiManager() {
    delete _gui;
}

void GuiManager::init() {
    img_level_selector.LoadFromFile("ressources/gui/level_selector.png");
    sp_level_selector.SetImage(img_level_selector);
    sp_level_selector.SetPosition(_app->GetWidth()/2 - img_level_selector.GetWidth()/2, _app->GetHeight()/2 - img_level_selector.GetHeight()/2);

    Menu* m = new Menu();
    _gui->add(m);

    std::vector<std::string> &list = MapManager::Instance()->getMapList();
    int y = 0;
    int x = 0;
    for(unsigned int i = 0; i < list.size(); i++) {
        std::stringstream st;
        st << i;
        Button *b = new Button(_game, st.str() , "ressources/gui/bloc_ouvert.png", list[i]);
        b->addTexture("ressources/gui/bloc_ouvert_hover.png");
        b->setPosition(sp_level_selector.GetPosition().x + 100 + x, sp_level_selector.GetPosition().y + 100 + y);
        m->add(b);

        if ((i % 4) == 0 && i > 0) {
            y += 60;
            x = 0;
        } else {
            x += 80;
        }
    }
}

void GuiManager::display() {
    bool run = true;
    _gui->setCurrentMenu(0);

    while(run) {
        sf::Event Event;
        const sf::Input& Input = _app->GetInput();

        while (_app->GetEvent(Event))  {
            if (Event.Type == sf::Event::Closed || (Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::Escape)) {
               run = false;
            } else {
                _gui->event(&Event, Input);
            }
        }

        _app->SetFramerateLimit(100);
        _app->Clear(sf::Color(125, 137, 255));

        _app->Draw(sp_level_selector);

        _gui->display();

        _app->SetView(_app->GetDefaultView());
        _app->Display();
    }

    _app->Close();
}
