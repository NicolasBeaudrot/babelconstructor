#include "Map.h"
#include <tinyxml.h>

Map::Map(sf::RenderWindow * application, sf::View* camera, const std::string &nom, b2World& world) : _app(application), _camera(camera){
    const std::string file = "ressources/map/" + nom;
    sf::Vector2f dimension;
    float limite_y;

    TiXmlDocument doc( file.c_str() );
    if (!doc.LoadFile()) {
        Logger::Instance()->log("Unable to load the map : " + file);
    } else {
        Logger::Instance()->log("Map loaded");

        TiXmlElement *back, *base, *limite, *elem;
        TiXmlHandle hdl(&doc);

        back = hdl.FirstChildElement("map").FirstChild("background").Element();

        base = hdl.FirstChildElement("map").FirstChild("support").Element();
        base->QueryFloatAttribute("width", &dimension.x);
        base->QueryFloatAttribute("height", &dimension.y);

        limite = hdl.FirstChildElement("map").FirstChild("limite").Element();
        limite->QueryFloatAttribute("y", &limite_y);

        ElementFactory::Instance()->loadBase(back->GetText(), base->GetText(), dimension, world, limite->GetText(), limite_y);

        elem = hdl.FirstChildElement("map").FirstChild("elements").FirstChildElement().Element();
        while (elem){
            sf::Vector2f position;
            float angle;
            float *fixture = new float[3];

            elem->QueryFloatAttribute("x", &position.x);
            elem->QueryFloatAttribute("y", &position.y);
            elem->QueryFloatAttribute("angle", &angle);
            elem->QueryFloatAttribute("density", &fixture[0]);
            elem->QueryFloatAttribute("friction", &fixture[1]);
            elem->QueryFloatAttribute("restitution", &fixture[2]);

            ElementFactory::Instance()->add(elem->Attribute("type"), position, angle, elem->Attribute("file"), world, fixture);
            elem = elem->NextSiblingElement();
        }
    }
}

Map::~Map() {
    ElementFactory::Instance()->Delete();
}

void Map::render(const sf::Input& input) {
    ElementFactory::Instance()->render(input);
}
