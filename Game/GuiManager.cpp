#include "GuiManager.h"
#include <sstream>

GuiManager::GuiManager() : _run(true) {
    _gui = NULL;
}

GuiManager::~GuiManager() {
    delete _gui;
    Logger::Instance()->log("GUI deleted");
}

void GuiManager::Init(sf::RenderWindow* app) {
    _app  = app;
    _gui = new Gui(_app);
    create();
}

void GuiManager::create() {

    //Menu Official Level Selector
    sf::Font *font = RessourceManager::Instance()->GetFont("ressources/fonts/gilligan.ttf");
    Menu* m = new Menu();
    _gui->add(m);

    Image *back_selector = new Image("image_selector", "ressources/gui/level_selector.png");
    back_selector->setPosition(_app->GetWidth()/2, _app->GetHeight()/2);
    m->add(back_selector);

    std::vector<std::string> &list = MapManager::Instance()->getMapList();
    int y = 0;
    int x = 0;
    for(unsigned int i = 0; i < list.size(); i++) {
        std::stringstream str_i, str_score;
        str_i << i;
        Button *b = new Button(str_i.str(), "ressources/gui/bloc_ouvert.png", "ressources/gui/bloc_ouvert_hover.png", list[i]);
        b->setPosition(back_selector->getPosition().x + 100 + x, back_selector->getPosition().y + 100 + y);
        m->add(b);

        if (ScoreManager::Instance()->getHightScore(list[i]) > 0) {
            str_score << (1./10.) * floor(ScoreManager::Instance()->getHightScore(list[i]) * 10.) << "\"";
        } else {
            str_score << "";
        }

        Label *l = new Label("time" + str_i.str(), str_score.str(), font, 14);
        l->setPosition(b->getPosition().x + 10, b->getPosition().y - 15);
        m->add(l);

        if ((i % 4) == 0 && i > 0) {
            y += 80;
            x = 0;
        } else {
            x += 80;
        }
    }

    //Menu Members Level Selector
    Menu* m2 = new Menu();
    _gui->add(m2);
    Image *back_selector_2 = new Image("image_selector", "ressources/gui/level_selector.png");
    back_selector_2->setPosition(_app->GetWidth()/2, _app->GetHeight()/2);
    m2->add(back_selector_2);

    Logger::Instance()->log("GUI loaded");
}

void GuiManager::refresh(int menu) {
    if (menu == 0) {
        std::vector<std::string> &list = MapManager::Instance()->getMapList();
        for(unsigned int i = 0; i < list.size(); i++) {
            if (ScoreManager::Instance()->getHightScore(list[i]) > 0) {
                std::stringstream str_i, str_score;
                str_i << i;
                Label *tmp = (Label*)_gui->getCurrentMenu()->get("time" + str_i.str());
                if (tmp) {
                    str_score << (1./10.) * floor(ScoreManager::Instance()->getHightScore(list[i]) * 10.) << "\"";
                    tmp->setText(str_score.str());
                }
            }
        }
    }
}

void GuiManager::display() {
    _gui->setCurrentMenu(0);
    bool run = true;

    while(run) {
        sf::Event Event;
        const sf::Input& Input = _app->GetInput();

        while (_app->GetEvent(Event))  {
            if (Event.Type == sf::Event::Closed || (Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::Escape)) {
               run = false;
            } else if (Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::M) {
                _gui->setCurrentMenu(1);
            }else {
                _gui->event(&Event, Input);
            }
        }

        _app->Clear(sf::Color(125, 137, 255));

        _gui->display();

        _app->SetView(_app->GetDefaultView());
        _app->Display();
    }
}
