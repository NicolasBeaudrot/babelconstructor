#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H
#include <QtCore>
#include <QListView>
#include <QStringListModel>

    class ItemFactory
    {
        private :
            QString _path;

        public :
            ItemFactory(QString image_path);

            void getList(QListView &l);
    };
#endif // ITEMFACTORY_H
