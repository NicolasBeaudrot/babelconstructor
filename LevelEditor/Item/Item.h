#ifndef ITEM_H
#define ITEM_H
#include <QString>

    class Item
    {
        private :
            QString _file;

        public :
            Item(QString file);

            QString getFile();
    };

#endif // ITEM_H
