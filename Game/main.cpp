#include <Box2D/Box2D.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "Utility/ImageManager.h"
#include "Utility/Logger.h"
#include "GuiManager.h"


int main(int argc, char** argv)
{
    Logger::Instance()->Init();
    GameManager *game = new GameManager();
    GuiManager *gui = new GuiManager(&game->getApp(), game);
    MapManager::Instance()->Init(&game->getApp());

    if (argc == 2) {
        game->run(argv[1]);
    } else {
        gui->display();
    }

    delete gui;
    delete game;

    MapManager::Kill();
    RessourceManager::Kill();
    Logger::Kill();

	return 0;
}
