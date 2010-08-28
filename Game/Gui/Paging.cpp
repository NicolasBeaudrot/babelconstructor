#include "Paging.h"
#include <sstream>
#include "../GuiManager.h"

Paging::Paging(std::string name, int total, int element_per_page) : Widget(name), _element_per_page(element_per_page), _total(total) {
    int pages = ceil((float)_total / _element_per_page);

    for(int i = 0; i < pages; i++) {
        std::stringstream str_i;
        str_i << (i+1);
        sf::String *page = new sf::String(str_i.str());
        page->SetFont(*RessourceManager::Instance()->GetFont("ressources/fonts/gilligan.ttf"));
        _arrPage.push_back(page);
    }
    _current_page = 0;
    _hover = false;
}

bool Paging::intersect(float x, float y) {
    for (unsigned int i = 0; i < _arrPage.size(); i++) {
        if (_arrPage[i]->GetPosition().x <= x && (_arrPage[i]->GetPosition().x + _arrPage[i]->GetRect().GetWidth()) >= x
            && _arrPage[i]->GetPosition().y <= y && (_arrPage[i]->GetPosition().y + _arrPage[i]->GetRect().GetHeight())) {
            _page_focused = i;
            return true;
        }
    }
    _hover = false;
    return false;
}

void Paging::onClic(int bouton) {
    _current_page = _page_focused;
    GuiManager::Instance()->displayPage();
}

void Paging::onHover() {
    _hover = true;
}

void Paging::setPosition(float x, float y) {
    for (unsigned int i = 0; i < _arrPage.size(); i++) {
        _arrPage[i]->SetPosition(x + i*30, y);
    }
}

sf::Vector2f Paging::getPosition() {
    if (_arrPage.size() > 0) {
        return _arrPage[0]->GetPosition();
    } else {
        return sf::Vector2f(0,0);
    }
}

sf::Vector2f Paging::getPageLimit() {
    return sf::Vector2f(_current_page * _element_per_page, (_current_page + 1) * _element_per_page);
}

unsigned int Paging::getTotal() {
    return _total;
}

void Paging::display(sf::RenderWindow* app) {
    for (unsigned int i = 0; i < _arrPage.size(); i++) {
        if (i == _current_page) {
            _arrPage[i]->SetColor(sf::Color::Blue);
        } else if (_hover && i == _page_focused) {
            _arrPage[i]->SetColor(sf::Color::Black);
        } else {
            _arrPage[i]->SetColor(sf::Color::White);
        }
        app->Draw(*_arrPage[i]);
    }
}
