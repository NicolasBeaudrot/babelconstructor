/*
    Copyright (C) 2010  Nicolas Beaudrot, Vincent Durey

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <Box2D/Box2D.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "Utility/RessourceManager.h"
#include "Utility/Logger.h"
#include "Utility/ScoreManager.h"
#include "GuiManager.h"
#include <SFML/Network.hpp>

int main(int argc, char** argv)
{
    Logger::Instance()->Init();
    ScoreManager::Instance()->parse("ressources/config.xml");
    GameManager::Instance()->Init();
    MapManager::Instance()->Init(&GameManager::Instance()->getApp());
    GuiManager::Instance()->Init(&GameManager::Instance()->getApp());

    if (argc == 2) {
        GameManager::Instance()->run(argv[1]);
    } else {
        GuiManager::Instance()->display();
    }

    MapManager::Kill();
    GuiManager::Kill();
    GameManager::Kill();
    ScoreManager::Kill();
    RessourceManager::Kill();
    Logger::Kill();

	return 0;
}
