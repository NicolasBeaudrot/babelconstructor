#include "Tab.h"

Tab::Tab(std::string name, std::string texture1, std::string texture2, Gui *gui, int menu) : Widget(name), _menu_id(menu) {
    addTexture(texture1);
    addTexture(texture2);
    _gui = gui;
}

bool Tab::intersect(float x, float y) {
    if (_arrSprites[0].GetPosition().x <= x && _arrSprites[0].GetPosition().x + _arrImages[0]->GetWidth() >= x
        && _arrSprites[0].GetPosition().y <= y && _arrSprites[0].GetPosition().y + _arrImages[0]->GetHeight() >= y) {
        return true;
    } else {
        return false;
    }
}

void Tab::onClic(int bouton) {
    if (_menu_id == 1) {
        MapManager::Instance()->setOfficialMode(true);
    } else {
        MapManager::Instance()->setOfficialMode(false);
    }
    _gui->setCurrentMenu(_menu_id);
}

void Tab::onHover() {
}

void Tab::setPosition(float x, float y) {
    for (unsigned int i = 0; i < _arrSprites.size(); i++) {
        _arrSprites[i].SetPosition(x, y);
    }
}

sf::Vector2f Tab::getPosition() {
    return _arrSprites[0].GetPosition();
}

float Tab::getHeight() {
    return _arrImages[0]->GetHeight();
}

float Tab::getWidth() {
    return _arrImages[0]->GetWidth();
}

void Tab::display(sf::RenderWindow* app) {
    if (_visible ) {
        if ( _gui->getCurrentMenu()->getId() == _menu_id ) {
            app->Draw(_arrSprites[1]);
        } else {
            app->Draw(_arrSprites[0]);
        }
    }
}
