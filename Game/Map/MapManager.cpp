#include "MapManager.h"

MapManager::MapManager() :
                    _app(NULL),
                    _camera(NULL) {
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
        Logger::Instance()->log("Map directory listed");
    } else {
        Logger::Instance()->log("Unable to open maps' directory");
    }
}

MapManager::~MapManager() {
    _tabMap.clear();
    delete _currentMap;
    Logger::Instance()->log("Map deleted");
}

void MapManager::Init(sf::RenderWindow* windows, sf::View* camera) {
	_app = windows;
	_camera = camera;
}

bool MapManager::nextMap() {
    _indexCurr++;
    delete _currentMap;
    if (_indexCurr < _tabMap.size()) {
        _currentMap = new Map(_app, _camera, _tabMap[_indexCurr]);
    } else {
        _indexCurr = 0;
        _currentMap = new Map(_app, _camera, _tabMap[_indexCurr]);
        return false;
    }
    return true;
}

void MapManager::reLoad() {
    delete _currentMap;
    _currentMap = new Map(_app, _camera, _tabMap[_indexCurr]);
}

