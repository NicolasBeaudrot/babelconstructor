#include <Box2D/Box2D.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "GameManager.h"

int main(int argc, char** argv)
{

    GameManager *game = new GameManager();

    game->run();

    delete game;

	return 0;
}
