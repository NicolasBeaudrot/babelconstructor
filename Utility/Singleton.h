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



