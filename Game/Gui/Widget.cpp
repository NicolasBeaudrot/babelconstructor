#include "Widget.h"

Widget::Widget(GameManager* game, std::string name) {
    _game = game;
    _visible = true;
    _name = name;
}

Widget::~Widget() {
}

std::string Widget::getName() {
    return _name;
}

bool Widget::getVisibility() {
    return _visible;
}

void Widget::setName(std::string name) {
    _name = name;
}

void Widget::setVisibility(bool visible) {
    _visible = visible;
}

void Widget::addTexture(std::string path) {
    _arrImages.push_back(RessourceManager::Instance()->GetImage(path));
    sf::Sprite sp;
    sp.SetImage(*RessourceManager::Instance()->GetImage(path));
    _arrSprites.push_back(sp);
}
