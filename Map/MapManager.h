#ifndef MAP_MANAGER
#define MAP_MANAGER
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Utility/Singleton.h"
#include "Map.h"
#include <dirent.h>

    class MapManager : public CSingleton<MapManager>
    {
        private:
            friend class CSingleton<MapManager>;
            MapManager();
            virtual ~MapManager();
            sf::RenderWindow* _app;
            sf::View* _camera;
            std::vector<std::string> _tabMap;
            int _indexCurr;

        public:
            void Init(sf::RenderWindow* window, sf::View* camera);

            void Load(const std::string& nom, b2World& world);

            Map* getCurrentMap;

            bool nextMap(b2World& world);
    };

#endif
