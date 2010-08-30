#include "Label.h"

Label::Label(std::string name, std::string text, sf::Font *font, int size) : Widget(name) {
    _text.SetText(text);
    _text.SetFont(*font);
    _text.SetSize(size);
    _text.SetColor(sf::Color::Black);
}

void Label::setText(std::string text) {
    _text.SetText(text);
}

void Label::setFont(sf::Font *font) {
    _text.SetFont(*font);
}

void Label::setSize(int size) {
    _text.SetSize(size);
}

void Label::setColor(const sf::Color& color) {
    _text.SetColor(color);
}

void Label::setPosition(float x, float y) {
    _text.SetPosition(x, y);
}

sf::Vector2f Label::getPosition() {
    return _text.GetPosition();
}

float Label::getWidth() {
    return _text.GetRect().GetWidth();
}

void Label::display(sf::RenderWindow* app) {
    app->Draw(_text);
}
