#include "Map.h"
#include <tinyxml.h>

Map::Map(sf::RenderWindow * application, const std::string &map) : _app(application) {
    const std::string file = "ressources/map/" + map;
    sf::Vector2f dimension;
    sf::Vector2f base_position;
    float limite_y = 0;

    TiXmlDocument doc( file.c_str() );
    if (!doc.LoadFile()) {
        Logger::Instance()->log("Unable to load the map : " + file);
    } else {
        Logger::Instance()->log("Map " + file + " loaded");

        try {
            TiXmlElement *back, *base, *limite, *elem;
            TiXmlHandle hdl(&doc);

            back = hdl.FirstChildElement("map").FirstChild("background").Element();

            base = hdl.FirstChildElement("map").FirstChild("support").Element();
            base->QueryFloatAttribute("width", &dimension.x);
            base->QueryFloatAttribute("height", &dimension.y);

            limite = hdl.FirstChildElement("map").FirstChild("limite").Element();
            limite->QueryFloatAttribute("y", &limite_y);


            base_position = ElementFactory::Instance()->loadBase(back->GetText(), base->GetText(), dimension, limite->GetText(), limite_y);

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

                if (elem->Attribute("type") != NULL && elem->Attribute("file") != NULL
                    && fixture[0] > 1 && fixture[1] >= 0 && fixture[1] <= 1 && fixture[2] >= 0 && fixture[2] <= 1) {
                    ElementFactory::Instance()->add(elem->Attribute("type"), position, angle, elem->Attribute("file"), fixture);
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
                if (elem->Attribute("type") != NULL && elem->Attribute("file") != NULL) {
                    ObstacleFactory::Instance()->add(elem->Attribute("type"), position, angle, elem->Attribute("file"), base_position);
                }
                elem = elem->NextSiblingElement();
            }
        } catch(...) {
            Logger::Instance()->log("The map structure is unknown !");
        }
    }
}

Map::~Map() {
    ElementFactory::Instance()->Delete();
    ObstacleFactory::Instance()->Delete();
    Logger::Instance()->log("Map deleted");
}
