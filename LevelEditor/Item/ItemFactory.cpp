#include "ItemFactory.h"

ItemFactory::ItemFactory(QString image_path) : _path(image_path){
}

void ItemFactory::getList(QListView &l) {
    QStringList files = QDir( _path ).entryList(QDir::Files | QDir::NoDotAndDotDot);
    l.setModel(new QStringListModel(files));
}
