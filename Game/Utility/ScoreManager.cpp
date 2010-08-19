#include "ScoreManager.h"
#include <tinyxml.h>

ScoreManager::ScoreManager() {
}

ScoreManager::~ScoreManager() {
}

void ScoreManager::parse(std::string path) {
    bool loaded = false;
    TiXmlDocument doc(path.c_str());

    if (doc.LoadFile()) {
        TiXmlElement *score = doc.FirstChildElement("game");
        if (score) {
            score = score->FirstChildElement("scores");
            if (score) {
                score = score->FirstChildElement();
                while (score) {
                    float value;
                    score->QueryFloatAttribute("value", &value);
                    _arrScore.insert(std::pair<std::string, float>(score->GetText(), value));

                    score = score->NextSiblingElement();
                }
                loaded = true;
            }
        }
    }
    Logger::Instance()->log("Score file parsed");
    if (!loaded) {
        Logger::Instance()->log("Unable to load the score file");
    }
}

void ScoreManager::update(std::string map, float score) {
    std::map<std::string, float>::iterator it;
    it = _arrScore.find(map);

    if(it == _arrScore.end()) {
        _arrScore.insert(std::pair<std::string, float>(map, score));
    } else {
        if (it->second > score) {
            it->second = score;
        }
    }
}

void ScoreManager::save(std::string path) {
    TiXmlDocument doc(path.c_str());
    bool saved = false;

    if (doc.LoadFile()) {
        TiXmlElement *elements = doc.FirstChildElement("game");
        if (elements) {
            elements = elements->FirstChildElement("scores");
            if (elements) {
                std::map<std::string, float>::iterator it;
                it = _arrScore.begin();

                while (it != _arrScore.end()) {
                    TiXmlElement *elem = elements->FirstChildElement();
                    bool create = true;
                    while (elem) {
                        if (elem->GetText() == it->first) {
                            elem->SetDoubleAttribute("value", it->second);
                            create = false;
                            break;
                        }
                        elem = elem->NextSiblingElement();
                    }

                    if (create) {
                        TiXmlElement *score = new TiXmlElement( "score" );
                        elements->LinkEndChild(score);
                        TiXmlText * text = new TiXmlText( it->first.c_str() );
                        score->LinkEndChild( text );
                        score->SetDoubleAttribute("value", it->second);
                    }
                    it++;
                }
                saved = true;
            }
        }
    }
    if ( saved ) {
        doc.SaveFile(path.c_str());
        Logger::Instance()->log("Scores saved");
    } else {
        Logger::Instance()->log("Unable to save scores");
    }
}

float ScoreManager::getHightScore(std::string map) {
    std::map<std::string, float>::iterator it;
    it = _arrScore.find(map);

    if(it == _arrScore.end()) {
        return 0;
    } else {
        return it->second;
    }
}
