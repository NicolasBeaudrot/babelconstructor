#include "MapManager.h"
#include <algorithm>

MapManager::MapManager() :
                    _app(NULL) {
    _currentMap = NULL;
    _indexCurr = -1;
    _official = true;
    listDir("./ressources/map/official", true);
    listDir("./ressources/map/unofficial", false);
    std::sort (_tabOfficialMap.begin(), _tabOfficialMap.end());
    std::sort (_tabUnofficialMap.begin(), _tabUnofficialMap.end());
}

MapManager::~MapManager() {
    _tabOfficialMap.clear();
    _tabUnofficialMap.clear();
    delete _currentMap;
}

void MapManager::Init(sf::RenderWindow* windows) {
	_app = windows;
}

void MapManager::load(std::string filename) {
    delete _currentMap;
    _indexCurr = 0;
    if (_official) {
        for (unsigned int i=0; i < _tabOfficialMap.size(); i++) {
            if (_tabOfficialMap[i] == filename) {
                _indexCurr = i;
                _currentMap = new Map(_app, _tabOfficialMap[_indexCurr]);
                break;
            }
        }

    } else {
        for (unsigned int i=0; i < _tabUnofficialMap.size(); i++) {
            if (_tabUnofficialMap[i] == filename) {
                _indexCurr = i;
                break;
            }
        }
        _currentMap = new Map(_app, _tabUnofficialMap[_indexCurr]);
    }

}

bool MapManager::nextMap() {
    _indexCurr++;
    int size;
    delete _currentMap;
    if (_official) {
        size = _tabOfficialMap.size();
    } else {
        size = _tabUnofficialMap.size();
    }

    if (_indexCurr < size) {
        if (_official) {
            _currentMap = new Map(_app, _tabOfficialMap[_indexCurr]);
        } else {
            _currentMap = new Map(_app, _tabUnofficialMap[_indexCurr]);
        }
    } else {
        _indexCurr = 0;
        if (_official) {
            _currentMap = new Map(_app, _tabOfficialMap[_indexCurr]);
        } else {
             _currentMap = new Map(_app, _tabUnofficialMap[_indexCurr]);
        }
        return false;
    }
    return true;
}

void MapManager::reLoad() {
    delete _currentMap;
    if (_official) {
        _currentMap = new Map(_app, _tabOfficialMap[_indexCurr]);
    } else {
        _currentMap = new Map(_app, _tabUnofficialMap[_indexCurr]);
    }
}

void MapManager::stop() {
    delete _currentMap;
    _currentMap = NULL;
}

std::string MapManager::getCurrentMapName() {
    if (_official) {
        return _tabOfficialMap[_indexCurr];
    } else {
        return _tabUnofficialMap[_indexCurr];
    }
}

std::vector<std::string>& MapManager::getMapList(bool official) {
    if (official) {
        return _tabOfficialMap;
    } else {
        return _tabUnofficialMap;
    }
}

void MapManager::listDir(std::string path, bool official) {
    DIR * rep = opendir(path.c_str());
    if (rep != NULL) {
        struct dirent * ent;
        while ((ent = readdir(rep)) != NULL) {
            std::string file = ent->d_name;
            int pos = file.length();

            while(pos > 0) {
                if(file[pos] == '.') {
                    break;
                }
                pos--;
            }
            if (file.substr(pos + 1, file.length() - pos - 1) == "xml") {
                if (official) {
                    _tabOfficialMap.push_back("official/" + file);
                } else {
                    _tabUnofficialMap.push_back("unofficial/" + file);
                }
            }
        }
        closedir(rep);
        Logger::Instance()->log(path + " listed");
    } else {
        Logger::Instance()->log("Unable to open " + path);
    }
}

bool MapManager::isOfficialMode() {
    return _official;
}

void MapManager::setOfficialMode(bool status) {
    _official = status;
}
