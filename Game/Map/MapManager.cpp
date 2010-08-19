#include "MapManager.h"
#include <algorithm>

MapManager::MapManager() :
                    _app(NULL) {
    _currentMap = NULL;
    _indexCurr = -1;
    DIR * rep = opendir("./ressources/map");

    if (rep != NULL) {
        struct dirent * ent;
        while ((ent = readdir(rep)) != NULL)
        {
            std::string file = ent->d_name;
            int pos = file.length();

            while(pos > 0) {
                if(file[pos] == '.') {
                    break;
                }
                pos--;
            }
            if (file.substr(pos + 1, file.length() - pos - 1) == "xml") {
                _tabMap.push_back(file);
            }
        }
        closedir(rep);
        std::sort (_tabMap.begin(), _tabMap.end());

        Logger::Instance()->log("Map directory listed");
    } else {
        Logger::Instance()->log("Unable to open maps' directory");
    }
}

MapManager::~MapManager() {
    _tabMap.clear();
    delete _currentMap;
}

void MapManager::Init(sf::RenderWindow* windows) {
	_app = windows;
}

void MapManager::load(std::string filename) {
    delete _currentMap;
    _indexCurr = 0;
    for (unsigned int i=0; i < _tabMap.size(); i++) {
        if (_tabMap[i] == filename) {
            _indexCurr = i;
            break;
        }
    }
    _currentMap = new Map(_app, _tabMap[_indexCurr]);
}

bool MapManager::nextMap() {
    _indexCurr++;
    delete _currentMap;
    if (_indexCurr < _tabMap.size()) {
        _currentMap = new Map(_app, _tabMap[_indexCurr]);
    } else {
        _indexCurr = 0;
        _currentMap = new Map(_app, _tabMap[_indexCurr]);
        return false;
    }
    return true;
}

void MapManager::reLoad() {
    delete _currentMap;
    _currentMap = new Map(_app, _tabMap[_indexCurr]);
}

void MapManager::stop() {
    delete _currentMap;
    _currentMap = NULL;
}

std::string MapManager::getCurrentMapName() {
    return _tabMap[_indexCurr];
}

std::vector<std::string>& MapManager::getMapList() {
    return _tabMap;
}
