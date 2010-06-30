#include "ElementFactory.h"

ElementFactory::ElementFactory() : _app(NULL) {
}

ElementFactory::~ElementFactory() {
}

void ElementFactory::Init(sf::RenderWindow *application) {
    _app = application;

    _mouse.SetColor(sf::Color::Black);
    _mouse.Resize(2,2);
    _mouse.SetCenter(0, 0);
}

void ElementFactory::Delete() {
    for (unsigned int i=0 ; i < _tabElem.size() ; i++) {
        delete _tabElem[i];
    }
    _tabElem.clear();
}

void ElementFactory::loadBase(std::string background, std::string base, sf::Vector2f& dimension, b2World& world, std::string limite, float limite_y) {
    _img_back.LoadFromFile("ressources/images/" + background);
    _sprite_back.SetImage(_img_back);
    _sprite_back.Resize(_app->GetWidth(), _app->GetHeight());
    Logger::Instance()->log("Background loaded");

    _img_limite.LoadFromFile("ressources/images/" + limite);
    _sprite_limite.SetImage(_img_limite);
    _sprite_limite.SetPosition(_app->GetWidth() - _img_limite.GetWidth(), limite_y);
    Logger::Instance()->log("Limite loaded");

    _img_base.LoadFromFile("ressources/images/" + base);
    _sprite_base.SetImage(_img_base);
    _sprite_base.Resize(dimension.x, dimension.y);
    _sprite_base.SetPosition(sf::Vector2f(_app->GetWidth()/2 - dimension.x/2, _app->GetHeight() - 100));
    Logger::Instance()->log("Base loaded");

	b2BodyDef baseBodyDef;
	baseBodyDef.position.Set((_app->GetWidth()/2), 90);
	b2Body* baseBody = world.CreateBody(&baseBodyDef);
	b2PolygonShape baseBox;
	baseBox.SetAsBox(dimension.x / 2.0f, 10.0f);
	baseBody->CreateFixture(&baseBox, 0.0f);
}

void ElementFactory::add(std::string type, sf::Vector2f& position, float& angle, std::string file, b2World& world, float* fixture) {
    if (type == "Square" or type == "Rectangle") {
        Square *elem = new Square(position, angle, file, world, fixture, _app);
        _tabElem.push_back(elem);
    } else if (type == "Circle") {
        Circle *elem = new Circle(position, angle, file, world, fixture, _app);
        _tabElem.push_back(elem);
    } else if (type == "Triangle") {
        Triangle *elem = new Triangle(position, angle, file, world, fixture, _app);
        _tabElem.push_back(elem);
    }
}

void ElementFactory::clic(const sf::Input& input) {

    if (input.GetMouseX() >= 0 && input.GetMouseX() <= _app->GetWidth()
        && input.GetMouseY() >= 0 && input.GetMouseY() <= _app->GetHeight()
        && !(input.GetMouseX() >= _sprite_base.GetPosition().x && input.GetMouseX() <= (_sprite_base.GetPosition().x + _img_base.GetWidth())
            && input.GetMouseY() >= _sprite_base.GetPosition().y && input.GetMouseY() <= _app->GetHeight())) {

        sf::Vector2f mouse = sf::Vector2f(input.GetMouseX(),input.GetMouseY());
        _mouse.SetPosition(mouse);

        for(unsigned int i=0 ; i <  _tabElem.size() ; i++) {
            _tabElem[i]->clic(_mouse);
            if (_tabElem[i]->test(_sprite_limite.GetPosition().y)) {
                Logger::Instance()->log("Gagné");
            }
        }
    }

}

void ElementFactory::rotate(int value) {
    for (unsigned int i=0 ; i < _tabElem.size() ; i++) {
        _tabElem[i]->rotate(value);
    }
}

void ElementFactory::render(const sf::Input& input) {
    _app->Draw(_sprite_back);
    _app->Draw(_sprite_base);
    _app->Draw(_sprite_limite);
   for(unsigned int i=0 ; i <  _tabElem.size() ; i++) {
        _tabElem[i]->render(input);
   }

}
