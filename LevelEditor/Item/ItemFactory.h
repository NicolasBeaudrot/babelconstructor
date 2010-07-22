#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H
#include <QtCore>
#include <QListView>
#include <QStringListModel>
#include "Item.h"

    class ItemFactory
    {
        private :
            QString _path;
            QHash<int, Item*> _elementsArray;
            QHash<int, Item*> _obstaclesArray;
        public :
            ItemFactory(QString image_path);

            void getList(QListView &l, int type);

            void setPath(QString image_path);

            QString getFile(int index, int type);
    };
#endif // ITEMFACTORY_H
