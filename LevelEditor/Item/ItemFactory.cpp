#include "ItemFactory.h"

ItemFactory::ItemFactory(QString image_path) : _path(image_path){
}

void ItemFactory::getList(QListView &l, int type) {
    QStringList files = QDir( _path ).entryList(QDir::Files | QDir::NoDotAndDotDot);
    l.setModel(new QStringListModel(files));

    if (type == 1) { //Elements
        for(int i=0; i < files.size(); i++) {
            _elementsArray.insert(i, new Item(_path + "/" + files[i]));
        }
    } else if (type == 2) { //Obstacles
        for(int i=0; i < files.size(); i++) {
            _obstaclesArray.insert(i, new Item(_path + "/" + files[i]));
        }
    }
}

void ItemFactory::setPath(QString image_path) {
    _path = image_path;
}

QString ItemFactory::getFile(int index, int type) {
    if (type == 1) {
        return _elementsArray[index]->getFile();
    } else if(type == 2) {
        return _obstaclesArray[index]->getFile();
    }
}
