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
#ifndef SINGLETON
#define SINGLETON

#include <iostream>

template<typename T> class CSingleton {

    public:

        static T* Instance(void) {
            if(singleton==0) {
                singleton = new T;
            }
            return singleton;
        }

        static void Kill() {
            if(singleton!=0) {
                delete singleton ;
                singleton=0;
            }
        }

    protected:

        CSingleton() {
        }

        virtual ~CSingleton() {
        }

        static T *singleton;
};

template <typename T> T* CSingleton<T>::singleton = 0;

#endif



