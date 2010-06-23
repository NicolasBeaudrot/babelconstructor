#ifndef LOGGER_H
#define LOGGER_H
#include "Singleton.h"
#include <iostream>

    class Logger : public CSingleton<Logger>
    {
        private :
            friend class CSingleton<Logger>;
            Logger();
            virtual ~Logger();

        public :
            void Init();
            void log(std::string message);
    };

#endif
