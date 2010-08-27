#include "Button.h"
#include "../GuiManager.h"

Button::Button(std::string name, std::string texture1, std::string texture2, std::string action) : Widget(name) {
    addTexture(texture1);
    addTexture(texture2);
    _hover = false;
    _action = action;
    _font = RessourceManager::Instance()->GetFont("ressources/fonts/gilligan.ttf");
    _name.SetFont(*_font);
    _name.SetText(name);
}

bool Button::intersect(float x, float y) {
    if (_arrSprites[0].GetPosition().x <= x && _arrSprites[0].GetPosition().x + _arrImages[0]->GetWidth() >= x
        && _arrSprites[0].GetPosition().y <= y && _arrSprites[0].GetPosition().y + _arrImages[0]->GetHeight() >= y) {
        return true;
    } else {
        _hover = false;
        return false;
    }
}

void Button::onClic(int bouton) {
    GameManager::Instance()->run(_action);
    GuiManager::Instance()->refresh();
    _hover = false;
}

void Button::onHover() {
    _hover = true;
}

void Button::setPosition(float x, float y) {
    for (unsigned int i = 0; i < _arrSprites.size(); i++) {
        _arrSprites[i].SetPosition(x, y);
    }
    sf::FloatRect rect = _name.GetRect();
    _name.SetPosition(x + (_arrImages[0]->GetWidth() - rect.GetWidth())/2 , y + 8);
}

sf::Vector2f Button::getPosition() {
    return _arrSprites[0].GetPosition();
}

float Button::getHeight() {
    return _arrImages[0]->GetHeight();
}

float Button::getWidth() {
    return _arrImages[0]->GetWidth();
}

void Button::display(sf::RenderWindow* app) {
    if (_visible ) {
        if ( !_hover ) {
            app->Draw(_arrSprites[0]);
        } else {
            app->Draw(_arrSprites[1]);
        }
        app->Draw(_name);
    }
}
