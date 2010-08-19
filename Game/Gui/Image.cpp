#include "Image.h"

Image::Image(std::string name, std::string texture) : Widget(name) {
    addTexture(texture);
}

void Image::setPosition(float x, float y) {
    x -= _arrImages[0]->GetWidth()/2;
    y -= _arrImages[0]->GetHeight()/2;
    _arrSprites[0].SetPosition(x, y);
}

sf::Vector2f Image::getPosition() {
    return _arrSprites[0].GetPosition();
}

void Image::display(sf::RenderWindow* app) {
    app->Draw(_arrSprites[0]);
}
