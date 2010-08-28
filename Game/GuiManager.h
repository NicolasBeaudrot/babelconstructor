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
#ifndef UIMANAGER_H
#define UIMANAGER_H
#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "Gui/Gui.h"
#include "Gui/Button.h"
#include "Gui/Image.h"
#include "Gui/Label.h"
#include "Gui/Tab.h"
#include "Gui/Paging.h"

    class GuiManager : public CSingleton<GuiManager>
    {
        private :
            friend class CSingleton<GuiManager>;
            GuiManager();
            ~GuiManager();
            void create();

            sf::RenderWindow* _app;
            Gui *_gui;
            bool _run;

        public :
            void Init(sf::RenderWindow* app);
            void refresh();
            void displayPage();
            void display();
    };

#endif
