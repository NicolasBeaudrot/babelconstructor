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

        try {
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
                float angle = 0;
                float *fixture = new float[3];

                elem->QueryFloatAttribute("x", &position.x);
                elem->QueryFloatAttribute("y", &position.y);
                elem->QueryFloatAttribute("angle", &angle);
                elem->QueryFloatAttribute("density", &fixture[0]);
                elem->QueryFloatAttribute("friction", &fixture[1]);
                elem->QueryFloatAttribute("restitution", &fixture[2]);

                if (elem->Attribute("type") != NULL && position.x != NULL && position.y != NULL && elem->Attribute("file") != NULL
                    && fixture[0] > 1 && fixture[1] >= 0 && fixture[1] <= 1 && fixture[2] >= 0 && fixture[2] <= 1) {
                    ElementFactory::Instance()->add(elem->Attribute("type"), position, angle, elem->Attribute("file"), world, fixture);
                }
                elem = elem->NextSiblingElement();
            }

            elem = hdl.FirstChildElement("map").FirstChild("obstacles").FirstChildElement().Element();
            while (elem){
                sf::Vector2f position;
                float angle;

                elem->QueryFloatAttribute("x", &position.x);
                elem->QueryFloatAttribute("y", &position.y);
                elem->QueryFloatAttribute("angle", &angle);

                //ElementFactory::Instance()->add(elem->Attribute("type"), position, angle, elem->Attribute("file"), world, fixture);
                elem = elem->NextSiblingElement();
            }
        } catch(...) {
            Logger::Instance()->log("The map structure is unknown !");
        }
    }
}

Map::~Map() {
    ElementFactory::Instance()->Delete();
}
