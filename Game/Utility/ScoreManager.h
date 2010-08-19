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
#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H
#include "Singleton.h"
#include <map>
#include "Logger.h"

    class ScoreManager : public CSingleton<ScoreManager>
    {
        private :
            friend class CSingleton<ScoreManager>;
            ScoreManager();
            ~ScoreManager();
            std::map<std::string, float> _arrScore;

        public :
            /**
            * This function is used to parse the score file and to create a list of scores
            * @param path of the xml file
            */
            void parse(std::string path);

            /**
            * This function is used to add or update (only if the score is highter than the current one) a score into the list
            * @param map's name
            * @param score's value
            */
            void update(std::string map, float score);

            /**
            * This function is used to save list of scores into the xml file
            * @param path of the xml file
            */
            void save(std::string path);

            /**
            * This function is used to get a map's hightest score
            * @param name of the map
            */
            float getHightScore(std::string map);
    };

#endif
