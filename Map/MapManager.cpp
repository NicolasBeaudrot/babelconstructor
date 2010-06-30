#include "MapManager.h"

MapManager::MapManager() :
                    _app(NULL),
                    _camera(NULL) {
    getCurrentMap = NULL;
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
    }
}

MapManager::~MapManager() {
    _tabMap.clear();
}

void MapManager::Init(sf::RenderWindow* windows, sf::View* camera) {
	_app = windows;
	_camera = camera;
}

void MapManager::Load(const std::string& nom, b2World& world) {
    getCurrentMap = new Map(_app, _camera, nom, world);
}

bool MapManager::nextMap(b2World& world) {
    _indexCurr++;
    if (_indexCurr < _tabMap.size()) {
        getCurrentMap = new Map(_app, _camera, _tabMap[_indexCurr], world);
    } else {
        _indexCurr = 0;
        getCurrentMap = new Map(_app, _camera, _tabMap[_indexCurr], world);
        return false;
    }
    return true;
}

