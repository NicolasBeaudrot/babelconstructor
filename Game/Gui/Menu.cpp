#include "Menu.h"

Menu::Menu() {
    _visible = false;
}

Menu::~Menu() {
    for (unsigned int i = 0; i < _arrWidget.size(); i++) {
        delete _arrWidget[i];
    }
    std::cout << "Menu deleted" << std::endl;
}

void Menu::add(Widget *w) {
    _arrWidget.push_back(w);
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
