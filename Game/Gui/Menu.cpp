#include "Menu.h"

Menu::Menu(int id) : _id(id) {
    _visible = false;
}

Menu::~Menu() {
}

void Menu::add(Widget *w) {
    _arrWidget.push_back(w);
}

int Menu::getId() {
    return _id;
}

Widget* Menu::get(std::string name) {
    for(unsigned int i = 0; i < _arrWidget.size(); i++) {
        if (_arrWidget[i]->getName() == name) {
            return _arrWidget[i];
        }
    }
    return NULL;
}

void Menu::remove(std::string name) {
    for(unsigned int i = 0; i < _arrWidget.size(); i++) {
        if (_arrWidget[i]->getName() == name) {
            delete _arrWidget[i];
            _arrWidget.erase(_arrWidget.begin() + i);
            break;
        }
    }
}

void Menu::event(sf::Event *ev, const sf::Input& in) {
    if (ev->Type == sf::Event::MouseMoved) {
        for (unsigned int i = 0; i < _arrWidget.size(); i++) {
            if (_arrWidget[i]->intersect(ev->MouseMove.X, ev->MouseMove.Y)) {
                _arrWidget[i]->onHover();
            }
        }
    } else if (ev->Type == sf::Event::MouseButtonPressed) {
        for (unsigned int i = 0; i < _arrWidget.size(); i++) {
            if (_arrWidget[i]->intersect(in.GetMouseX(), in.GetMouseY())) {
                if (in.IsMouseButtonDown(sf::Mouse::Left)) {
                    _arrWidget[i]->onClic(1);
                } else {
                    _arrWidget[i]->onClic(2);
                }
            }
        }
    }
}

void Menu::setVisibility(bool visible) {
    _visible = visible;
}

void Menu::display(sf::RenderWindow* app) {
    if ( _visible ) {
        for (unsigned int i = 0; i < _arrWidget.size(); i++) {
            _arrWidget[i]->display(app);
        }
    }
}
