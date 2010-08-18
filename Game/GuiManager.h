#ifndef UIMANAGER_H
#define UIMANAGER_H
#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "Gui/Gui.h"

    class GuiManager
    {
        private :
            sf::RenderWindow* _app;
            GameManager* _game;
            Gui *_gui;
            sf::Image img_level_selector;
            sf::Sprite sp_level_selector;

        public :
            GuiManager(sf::RenderWindow* app, GameManager* game);
            ~GuiManager();
            void init();
            void display();
    };

#endif
