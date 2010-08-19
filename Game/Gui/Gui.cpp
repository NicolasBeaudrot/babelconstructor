#include "Gui.h"

Gui::Gui(sf::RenderWindow* app) {
    _app = app;
    _visible = true;
    _currentMenu = NULL;
}

Gui::~Gui() {
    for(unsigned int i=0; i < _arrMenus.size(); i++) {
        delete _arrMenus[i];
    }
}

void Gui::add(Menu *m) {
    _arrMenus.push_back(m);
    _currentMenu = _arrMenus[_arrMenus.size()-1];
}

Menu* Gui::getCurrentMenu() {
    return _currentMenu;
}

void Gui::event(sf::Event* ev, const sf::Input& in) {
    _currentMenu->event(ev, in);
}

void Gui::setCurrentMenu(int i) {
    _currentMenu = _arrMenus[i];
    _currentMenu->setVisibility(true);
}

void Gui::setVisibility(bool visible) {
    _visible = visible;
}

void Gui::display() {
    if ( _visible ) {
        _currentMenu->display(_app);
    }
}
