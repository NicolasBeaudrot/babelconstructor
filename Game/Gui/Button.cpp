#include "Button.h"

Button::Button(GameManager* game, std::string name, std::string texture, std::string action) : Widget(game, name) {
    addTexture(texture);
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
    _game->run(_action);
}

void Button::onHover() {
    _hover = true;
}

void Button::setPosition(float x, float y) {
    for (unsigned int i = 0; i < _arrSprites.size(); i++) {
        _arrSprites[i].SetPosition(x, y);
    }
    _name.SetPosition(x + 14, y + 8);
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