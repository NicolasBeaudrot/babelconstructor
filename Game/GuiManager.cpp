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

    //Menu Official Level
    sf::Font *font = RessourceManager::Instance()->GetFont("ressources/fonts/gilligan.ttf");
    Menu* m = new Menu(1);
    _gui->add(m);

    Image *back_selector = new Image("image_selector", "ressources/gui/level_selector.png");
    back_selector->setPosition(_app->GetWidth()/2, _app->GetHeight()/2);
    m->add(back_selector);

    Tab *official = new Tab("tab_official", "ressources/gui/onglet_official.png", "ressources/gui/onglet_official_hover.png", _gui, 1);
    official->setPosition(back_selector->getPosition().x + 80, back_selector->getPosition().y + 50);
    m->add(official);

    Tab *unofficial = new Tab("tab_unofficial", "ressources/gui/onglet_unofficial.png", "ressources/gui/onglet_unofficial_hover.png", _gui, 2);
    unofficial->setPosition(back_selector->getPosition().x + 450, back_selector->getPosition().y + 50);
    m->add(unofficial);

    std::vector<std::string> &list = MapManager::Instance()->getMapList();
    int y = 0, x = 0;
    bool initialized = false;
    for(unsigned int i = 0; i < list.size(); i++) {
        std::stringstream str_i, str_score;
        str_i << i;
        if (ScoreManager::Instance()->getHightScore(list[i]) > 0 || !initialized) {
            Button *b = new Button("btnOfficial" + str_i.str(), str_i.str(), "ressources/gui/bloc_ouvert.png", "ressources/gui/bloc_ouvert_hover.png", list[i]);
            b->setPosition(back_selector->getPosition().x + 100 + x, back_selector->getPosition().y + 100 + y);
            m->add(b);

            if (ScoreManager::Instance()->getHightScore(list[i]) == 0){
                initialized = true;
                str_score << "";
            } else {
                str_score << (1./10.) * floor(ScoreManager::Instance()->getHightScore(list[i]) * 10.) << "\"";
            }
            Label *l = new Label("time" + str_i.str(), str_score.str(), font, 14);
            l->setPosition(b->getPosition().x + 10, b->getPosition().y - 15);
            m->add(l);
        } else {
            Image* lock_b = new Image("img" + str_i.str(), "ressources/gui/bloc_cadenas.png");
            lock_b->setPosition(back_selector->getPosition().x + 120 + x, back_selector->getPosition().y + 125 + y);
            m->add(lock_b);
        }

        if ((i % 4) == 0 && i > 0) {
            y += 80;
            x = 0;
        } else {
            x += 80;
        }
    }

    //Menu Members Level
    Menu* m2 = new Menu(2);
    _gui->add(m2);
    m2->add(back_selector);
    m2->add(official);
    m2->add(unofficial);
    std::vector<std::string> &list2 = MapManager::Instance()->getMapList(false);

    Paging *pager = new Paging("pager", list2.size());
    pager->setPosition(back_selector->getPosition().x + 100, back_selector->getPosition().y + 330);
    m2->add(pager);

    for(unsigned int i = 0; i < list2.size(); i++) {
        std::stringstream str_i, str_score;
        str_i << i;
        Label *map = new Label("labelUnofficial" + str_i.str(), list2[i], font, 16);
        map->setPosition(back_selector->getPosition().x + 100,  back_selector->getPosition().y + 90 + i*50);
        m2->add(map);
        Button* go = new Button("btnUnofficial" + str_i.str(), "Go", "ressources/gui/bloc_ouvert.png", "ressources/gui/bloc_ouvert_hover.png", list2[i]);
        go->setPosition(map->getPosition().x + 450, map->getPosition().y - 20);
        m2->add(go);

        if (ScoreManager::Instance()->getHightScore(list2[i]) > 0) {
            str_score << (1./10.) * floor(ScoreManager::Instance()->getHightScore(list2[i]) * 10) << "\"";
        } else {
            str_score << "";
        }

        Label* score = new Label("scoreUnofficial" + str_i.str(), str_score.str(), font, 16);
        score->setPosition(map->getPosition().x + map->getWidth() + 20, map->getPosition().y);
        score->setColor(sf::Color::Red);
        m2->add(score);
    }
    displayPage();
    Logger::Instance()->log("GUI loaded");
}

void GuiManager::displayPage() {
    if (_gui->getCurrentMenu()->getId() == 2) {
        Paging *pager = (Paging*)_gui->getCurrentMenu()->get("pager");
        int y = 0;
        for (unsigned int i=0; i < pager->getTotal(); i++) {
            std::stringstream str_i;
            str_i << i;
            if (i >= pager->getPageLimit().x && i < pager->getPageLimit().y) {
                _gui->getCurrentMenu()->get("labelUnofficial" + str_i.str())->setVisibility(true);
                _gui->getCurrentMenu()->get("btnUnofficial" + str_i.str())->setVisibility(true);
                _gui->getCurrentMenu()->get("scoreUnofficial" + str_i.str())->setVisibility(true);
                _gui->getCurrentMenu()->get("labelUnofficial" + str_i.str())->setPosition(_gui->getCurrentMenu()->get("image_selector")->getPosition().x + 100,  _gui->getCurrentMenu()->get("image_selector")->getPosition().y + 90 + y*50);
                _gui->getCurrentMenu()->get("btnUnofficial" + str_i.str())->setPosition(_gui->getCurrentMenu()->get("image_selector")->getPosition().x + 450,  _gui->getCurrentMenu()->get("labelUnofficial" + str_i.str())->getPosition().y - 20);
                Label *tmp = (Label*)_gui->getCurrentMenu()->get("labelUnofficial" + str_i.str());
                _gui->getCurrentMenu()->get("scoreUnofficial" + str_i.str())->setPosition(tmp->getPosition().x + tmp->getWidth() + 20, tmp->getPosition().y);
                y++;
            } else {
                _gui->getCurrentMenu()->get("labelUnofficial" + str_i.str())->setVisibility(false);
                _gui->getCurrentMenu()->get("btnUnofficial" + str_i.str())->setVisibility(false);
                _gui->getCurrentMenu()->get("scoreUnofficial" + str_i.str())->setVisibility(false);
            }
        }
    }
}

void GuiManager::refresh() {
    sf::Font *font = RessourceManager::Instance()->GetFont("ressources/fonts/gilligan.ttf");

    if (_gui->getCurrentMenu()->getId() == 1) {
        std::vector<std::string> &list = MapManager::Instance()->getMapList();
        int x=0, y=0;
        for(unsigned int i = 0; i < list.size(); i++) {
            std::stringstream str_i, str_score;
            str_i << i;
            if (ScoreManager::Instance()->getHightScore(list[i]) > 0) {
                Label *tmp = (Label*)_gui->getCurrentMenu()->get("time" + str_i.str());
                if (tmp) {
                    str_score << (1./10.) * floor(ScoreManager::Instance()->getHightScore(list[i]) * 10.) << "\"";
                    tmp->setText(str_score.str());
                }
            } else {
                _gui->getCurrentMenu()->remove("img" + str_i.str());
                Button *b = new Button("btnOfficial" + str_i.str(), str_i.str(), "ressources/gui/bloc_ouvert.png", "ressources/gui/bloc_ouvert_hover.png", list[i]);
                b->setPosition(_gui->getCurrentMenu()->get("image_selector")->getPosition().x + 100 + x, _gui->getCurrentMenu()->get("image_selector")->getPosition().y + 100 + y);
                _gui->getCurrentMenu()->add(b);
                Label *l = new Label("time" + str_i.str(), "", font, 14);
                l->setPosition(b->getPosition().x + 10, b->getPosition().y - 15);
                _gui->getCurrentMenu()->add(l);
                break;
            }
            if ((i % 4) == 0 && i > 0) {
                y += 80;
                x = 0;
            } else {
                x += 80;
            }
        }
    } else if (_gui->getCurrentMenu()->getId() == 2) {
        std::vector<std::string> &list = MapManager::Instance()->getMapList(false);

        for(unsigned int i = 0; i < list.size(); i++) {
            std::stringstream str_i, str_score;
            str_i << i;
            if (ScoreManager::Instance()->getHightScore(list[i]) > 0) {
                Label *tmp = (Label*)_gui->getCurrentMenu()->get("scoreUnofficial" + str_i.str());
                if (tmp) {
                    str_score << (1./10.) * floor(ScoreManager::Instance()->getHightScore(list[i]) * 10.) << "\"";
                    tmp->setText(str_score.str());
                }
            }
        }
    }
}

void GuiManager::display() {
    _gui->setCurrentMenu(1);
    bool run = true;

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

        _app->Clear(sf::Color(125, 137, 255));

        _gui->display();

        _app->SetView(_app->GetDefaultView());
        _app->Display();
    }
}
