#include "SFMLCanvas.h"
#include <QMenuBar>
#include <QMenu>
#include <QStatusBar>

SFMLCanvas::SFMLCanvas(QWidget* Parent, Ui::MainWindow& u, const QPoint& Position, const QSize& Size)
 : QSFMLCanvas(Parent, Position, Size), _clicked(false)
{
    _win = &u;

    QMenuBar *menu = new QMenuBar( Parent );
    QMenu *fileMenu = new QMenu("&File", Parent);
    menu->addMenu( fileMenu );

    QAction * newAct = new QAction(tr("&New"), this);
    newAct->setShortcut(tr("Ctrl+N"));
    newAct->setStatusTip(tr("Create a new map"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(on_newMap()));
    fileMenu->addAction(newAct);

    QAction * openAct = new QAction(tr("&Open"), this);
    openAct->setShortcut(tr("Ctrl+O"));
    openAct->setStatusTip(tr("Open a map in the editor"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(on_loadMap()));
    fileMenu->addAction(openAct);

    QAction * saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcut(tr("Ctrl+S"));
    saveAct->setStatusTip(tr("Save the map"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(on_saveMap()));
    fileMenu->addAction(saveAct);

    QAction * saveasAct = new QAction(tr("&Save as"), this);
    saveasAct->setShortcut(tr("Ctrl+Shift+S"));
    saveasAct->setStatusTip(tr("Save the map in a new file"));
    connect(saveasAct, SIGNAL(triggered()), this, SLOT(on_saveAsMap()));
    fileMenu->addAction(saveasAct);

    QAction * quitAct = new QAction(tr("&Close"), this);
    quitAct->setShortcut(tr("Ctrl+Q"));
    quitAct->setStatusTip(tr("Close the editor"));
    connect(quitAct, SIGNAL(triggered()), this, SLOT(on_close()));
    fileMenu->addAction(quitAct);

    connect(_win->elementsListView, SIGNAL(clicked(QModelIndex)), this, SLOT(on_elementsListView_clicked(QModelIndex)));
    connect(_win->obstaclesListView, SIGNAL(clicked(QModelIndex)), this, SLOT(on_obstaclesListView_clicked(QModelIndex)));
    connect(_win->refreshButton, SIGNAL(clicked()), this, SLOT(on_refreshButton_clicked()));
    connect(_win->angleEdit, SIGNAL(sliderMoved(int)), this, SLOT(on_angleEdit_sliderMoved(int)));
    connect(_win->deleteButton, SIGNAL(clicked()), this, SLOT(on_deleteButton_clicked()));
    connect(_win->backgroundsListView, SIGNAL(clicked(QModelIndex)), this, SLOT(on_backgroundsListView_clicked(QModelIndex)));
    connect(_win->limiteEdit, SIGNAL(valueChanged(int)), this, SLOT(on_limiteEdit_valueChanged(int)));
    connect(_win->typeEdit, SIGNAL(currentIndexChanged(QString)), this, SLOT(on_typeEdit_currentIndexChanged(QString)));
    connect(_win->widthEdit, SIGNAL(valueChanged(double)), this, SLOT(on_widthEdit_valueChanged(double)));
    connect(_win->densityEdit, SIGNAL(valueChanged(double)), this, SLOT(on_densityEdit_valueChanged(double)));
    connect(_win->frictionEdit, SIGNAL(valueChanged(double)), this, SLOT(on_frictionEdit_valueChanged(double)));
    connect(_win->restitutionEdit, SIGNAL(valueChanged(double)), this, SLOT(on_restitutionEdit_valueChanged(double)));
    refreshItemsList();

    _items = new ItemFactory();
    _win->objectProperties->setFocus();
}

SFMLCanvas::~SFMLCanvas() {
    delete _items;
}

void SFMLCanvas::OnInit() {
    _win->objectProperties->setVisible(false);

    //First we load the base
    _base_image.LoadFromFile("ressources/images/barre.png");
    _base_sprite.SetImage(_base_image);
    _base_sprite.SetCenter(_base_sprite.GetSize() / 2.0f);
    _base_sprite.SetPosition(this->GetWidth()/2, this->GetHeight()-100);

    //Then we load the limit
    _limite_image.LoadFromFile("ressources/images/limite.png");
    _limite_sprite.SetImage(_limite_image);
    _limite_sprite.SetPosition(this->GetWidth() - _limite_image.GetWidth(), _base_sprite.GetPosition().y - _win->limiteEdit->text().toFloat());

}

void SFMLCanvas::refreshItemsList() {
    QStringList files = QDir( "ressources/images/elements" ).entryList(QDir::Files | QDir::NoDotAndDotDot);
    _win->elementsListView->setModel(new QStringListModel(files));
    files = QDir( "ressources/images/obstacles" ).entryList(QDir::Files | QDir::NoDotAndDotDot);
    _win->obstaclesListView->setModel(new QStringListModel(files));
    files = QDir( "ressources/images/backgrounds" ).entryList(QDir::Files | QDir::NoDotAndDotDot);
    _win->backgroundsListView->setModel(new QStringListModel(files));
}

void SFMLCanvas::mouseReleaseEvent  ( QMouseEvent * e ) {
    if (e->button() == Qt::LeftButton) {
        if (e->x() >= (_base_sprite.GetPosition().x - _base_image.GetWidth()/2) && e->x() <= (_base_sprite.GetPosition().x - _base_image.GetWidth()/2 + _base_image.GetWidth())
            && e->y() >= (_base_sprite.GetPosition().y - _base_image.GetHeight()/2) && e->y() <= (_base_sprite.GetPosition().y - _base_image.GetHeight()/2 + _base_image.GetHeight())) {
            _mode = 1;
            displayProperties();
        } else if (_items->isClicked(e->x(), e->y()) != -1) {
            _currentItem = _items->isClicked(e->x(), e->y());
            _mode = _items->getItemType(_currentItem);
            displayProperties();
        } else {
            _win->objectProperties->setVisible(false);
        }
        _clicked = false;
    } else {
        if(_clicked) {
            _items->remove(_currentItem);
            _clicked = false;
        }
    }
}

void SFMLCanvas::OnUpdate() {
    SetFramerateLimit(100);
    Clear(sf::Color(255, 255, 255));
    if( !_back_path.isEmpty() ) {
        Draw(_back_sprite);
    }
    Draw(_base_sprite);
    Draw(_limite_sprite);

    if (_clicked) {
        _items->setPosition(_currentItem, sf::Vector2f(QCursor::pos().x() - 150, QCursor::pos().y() - 80));
    }
    _items->render(*this);
}

void SFMLCanvas::displayProperties() {
    hideProperties();

    switch(_mode) {
        case 1 : { //Mode base
            _win->objectProperties->setTitle("Properties : Base");
            _win->widthEdit->setEnabled(true);
            _win->widthLabel->setVisible(true);
            _win->widthEdit->setVisible(true);
            _win->widthEdit->setValue(_base_sprite.GetSize().x);
        }
        break;
        case 2 : { //Mode Elements
            float *prop = _items->getProperties(_currentItem);
            QString s;
            _win->widthEdit->setValue(prop[0]);
            _win->heightEdit->setValue(prop[1]);
            _win->widthEdit->setEnabled(false);
            _win->heightEdit->setEnabled(false);
            _win->xEdit->setText(s.setNum(prop[2]));
            _win->yEdit->setText(s.setNum(prop[3]));
            _win->angleEdit->setValue(prop[4]);
            _win->densityEdit->setValue(prop[5]);
            _win->frictionEdit->setValue(prop[6]);
            _win->restitutionEdit->setValue(prop[7]);
            _win->typeEdit->setCurrentIndex(_win->typeEdit->findText(_items->getType(_currentItem)));
            _win->objectProperties->setTitle("Properties : Element " + _items->getTexture(_currentItem));
            _win->angleEdit->setVisible(true);
            _win->angleLabel->setVisible(true);
            _win->densityEdit->setVisible(true);
            _win->densityLabel->setVisible(true);
            _win->frictionEdit->setVisible(true);
            _win->frictionLabel->setVisible(true);
            _win->heightEdit->setVisible(true);
            _win->heigthLabel->setVisible(true);
            _win->restitutionEdit->setVisible(true);
            _win->restitutionLabel->setVisible(true);
            _win->widthEdit->setVisible(true);
            _win->widthLabel->setVisible(true);
            _win->xEdit->setVisible(true);
            _win->xLabel->setVisible(true);
            _win->yEdit->setVisible(true);
            _win->yLabel->setVisible(true);
            _win->typeEdit->setVisible(true);
            _win->typeLabel->setVisible(true);
            _win->deleteButton->setVisible(true);
        }
        break;
        case 3 : { //Mode Obstacles
            float *prop = _items->getProperties(_currentItem);
            QString s;
            _win->widthEdit->setValue(prop[0]);
            _win->heightEdit->setValue(prop[1]);
            _win->widthEdit->setEnabled(false);
            _win->heightEdit->setEnabled(false);
            _win->xEdit->setText(s.setNum(prop[2]));
            _win->yEdit->setText(s.setNum(prop[3]));
            _win->angleEdit->setValue(prop[4]);
            _win->typeEdit->setCurrentIndex(_win->typeEdit->findText(_items->getType(_currentItem)));
            _win->objectProperties->setTitle("Properties : Obstacle " + _items->getTexture(_currentItem));
            _win->angleEdit->setVisible(true);
            _win->angleLabel->setVisible(true);
            _win->heightEdit->setVisible(true);
            _win->heigthLabel->setVisible(true);
            _win->widthEdit->setVisible(true);
            _win->widthLabel->setVisible(true);
            _win->xEdit->setVisible(true);
            _win->xLabel->setVisible(true);
            _win->yEdit->setVisible(true);
            _win->yLabel->setVisible(true);
            _win->typeEdit->setVisible(true);
            _win->typeLabel->setVisible(true);
            _win->deleteButton->setVisible(true);
        }
        break;
    }

    _win->objectProperties->setVisible(true);
}

void SFMLCanvas::hideProperties() {
    _win->angleEdit->setVisible(false);
    _win->angleLabel->setVisible(false);
    _win->densityEdit->setVisible(false);
    _win->densityLabel->setVisible(false);
    _win->frictionEdit->setVisible(false);
    _win->frictionLabel->setVisible(false);
    _win->heightEdit->setVisible(false);
    _win->heigthLabel->setVisible(false);
    _win->restitutionEdit->setVisible(false);
    _win->restitutionLabel->setVisible(false);
    _win->widthEdit->setVisible(false);
    _win->widthLabel->setVisible(false);
    _win->xEdit->setVisible(false);
    _win->xLabel->setVisible(false);
    _win->yEdit->setVisible(false);
    _win->yLabel->setVisible(false);
    _win->typeEdit->setVisible(false);
    _win->typeLabel->setVisible(false);
    _win->deleteButton->setVisible(false);
    _win->objectProperties->setVisible(false);
}

void SFMLCanvas::keyPressEvent(QKeyEvent *key) {
    if (key->key() == Qt::Key_Up) {
        _items->move(_currentItem, -1, 1);
        displayProperties();
    } else if (key->key() == Qt::Key_Down) {
        _items->move(_currentItem, 1, 1);
        displayProperties();
    } else if (key->key() == Qt::Key_Left) {
        _items->move(_currentItem, -1, 0);
        displayProperties();
    } else if (key->key() == Qt::Key_Right) {
        _items->move(_currentItem, 1, 0);
        displayProperties();
    }
}

void SFMLCanvas::loadMap() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setDirectory("./ressources/map/unofficial");
    dialog.setNameFilter(tr("XML files (*.xml)"));
    QStringList fileNames;
    if (dialog.exec()) {
        fileNames = dialog.selectedFiles();
        _currentFile = fileNames.takeFirst();
        _items->reset();
        hideProperties();
        _clicked = false;
        modifyTitle();

        QDomDocument doc;
        QFile map(_currentFile);
        map.open(QFile::ReadOnly);
        doc.setContent(&map);
        map.close();

        QDomElement root=doc.documentElement();
        QDomElement child=root.firstChild().toElement();
        while(!child.isNull()) {
            if (child.tagName() == "background") {
                _back_path = child.text();
                _back_image.LoadFromFile("ressources/images/backgrounds/" + child.text().toStdString());
                _back_sprite.SetImage(_back_image);
                _back_sprite.Resize(GetWidth(), GetHeight());
            } else if (child.tagName() == "support") {
                _base_image.LoadFromFile("ressources/images/" + child.text().toStdString());
                _base_sprite.SetImage(_base_image);
                _base_sprite.Resize(child.attribute("width", "300").toFloat(), child.attribute("height", "30").toFloat());
            } else if (child.tagName() == "limite") {
                _limite_image.LoadFromFile("ressources/images/limite.png");
                _limite_sprite.SetImage(_limite_image);
                _limite_sprite.SetPosition(this->GetWidth() - _limite_image.GetWidth(), _base_sprite.GetPosition().y - child.attribute("y", "300").toFloat());
                _win->limiteEdit->setValue(child.attribute("y", "300").toInt());
            } else if (child.tagName() == "elements") {
                QDomElement grandChild=child.firstChild().toElement();
                while(!grandChild.isNull()) {
                    int index = _items->add(2, "ressources/images/elements/" + grandChild.attribute("file", "empty"));
                    float prop[8];
                    prop[2] = _base_sprite.GetPosition().x - (_base_sprite.GetSize().x/2) + grandChild.attribute("x", "empty").toFloat();
                    prop[3] = _base_sprite.GetPosition().y - (_base_sprite.GetSize().y/2) - grandChild.attribute("y", "empty").toFloat();
                    prop[4] = grandChild.attribute("angle", "empty").toFloat();
                    prop[5] = grandChild.attribute("density", "empty").toFloat();
                    prop[6] = grandChild.attribute("friction", "empty").toFloat();
                    prop[7] = grandChild.attribute("restitution", "empty").toFloat();
                    _items->setType(index, grandChild.attribute("type", "Square"));
                    _items->setProperties(index, prop);
                    grandChild = grandChild.nextSibling().toElement();
                }
            } else if (child.tagName() == "obstacles") {
                QDomElement grandChild=child.firstChild().toElement();
                while(!grandChild.isNull()) {
                    int index = _items->add(3, "ressources/images/obstacles/" + grandChild.attribute("file", "empty"));
                    float prop[8];
                    prop[2] = _base_sprite.GetPosition().x - (_base_sprite.GetSize().x/2) + grandChild.attribute("x", "empty").toFloat();
                    prop[3] = _base_sprite.GetPosition().y - (_base_sprite.GetSize().y/2) - grandChild.attribute("y", "empty").toFloat();
                    prop[4] = grandChild.attribute("angle", "empty").toFloat();
                    prop[5] = 0;
                    prop[6] = 0;
                    prop[7] = 0;
                    _items->setType(index, grandChild.attribute("type", "Square"));
                    _items->setProperties(index, prop);
                    grandChild = grandChild.nextSibling().toElement();
                }
            }
            child = child.nextSibling().toElement();
        }
    }
}

void SFMLCanvas::saveMap() {
    if (!_currentFile.isEmpty()) {
        QFile file(_currentFile);
        if (file.open(QFile::WriteOnly)) {
            QTextStream out(&file);
            out << "<?xml version=\"1.0\" ?>" << endl;
            out << "<map>" << endl;
            if (_back_path.isEmpty()) {
                _back_path = "empty";
            }
            if (_clicked) {
                _items->remove(_currentItem);
                _clicked = false;
            }
            out << "<background>" << _back_path << "</background>" << endl;
            out << "<support width=\"" << _base_sprite.GetSize().x << "\" height=\"" << _base_image.GetHeight() << "\">barre.png</support>" << endl;
            out << "<limite y=\"" << (_base_sprite.GetPosition().y - _limite_sprite.GetPosition().y) << "\">limite.png</limite>" << endl;
            out << _items->save(_base_sprite.GetPosition().x - (_base_sprite.GetSize().x/2), _base_sprite.GetPosition().y - (_base_sprite.GetSize().y/2)) << endl;
            out << "</map>";
            modifyTitle();
        }
        file.close();
    } else {
        saveAsMap();
    }

}

void SFMLCanvas::saveAsMap() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setDirectory("./ressources/map/unofficial");
    dialog.setNameFilter(tr("XML files (*.xml)"));
    QStringList fileNames;
    if (dialog.exec()) {
        fileNames = dialog.selectedFiles();
        _currentFile = fileNames.takeFirst();
        if (!_currentFile.endsWith(".xml")) {
            _currentFile += ".xml";
        }
        saveMap();
    }
}

void SFMLCanvas::newMap() {
    _items->reset();
    _clicked = false;
    _back_path = "";
    _currentFile = "";
    modifyTitle();
    _base_sprite.Resize(300, _base_image.GetHeight());
     _win->limiteEdit->setValue(300);
    _limite_sprite.SetY(_base_sprite.GetPosition().y - _win->limiteEdit->text().toFloat());
    hideProperties();
}

void SFMLCanvas::modifyTitle(bool change) {
    QString title = "Babel Level Editor - " + _currentFile;
    if (change) {
        title += "*";
    }
    this->parentWidget()->setWindowTitle(title);
}

void SFMLCanvas::on_widthEdit_valueChanged(double value) {
    if (_mode == 1) {
        _base_sprite.Resize(value, _base_image.GetHeight());
        modifyTitle(true);
    }
}

void SFMLCanvas::on_densityEdit_valueChanged(double value) {
    _items->setProperty(_currentItem, 5, value);
    modifyTitle(true);
}

void SFMLCanvas::on_frictionEdit_valueChanged(double value) {
    _items->setProperty(_currentItem, 6, value);
    modifyTitle(true);
}

void SFMLCanvas::on_restitutionEdit_valueChanged(double value) {
    _items->setProperty(_currentItem, 7, value);
    modifyTitle(true);
}

void SFMLCanvas::on_elementsListView_clicked(QModelIndex index) {
    _clicked = true;
    _currentItem = _items->add(2,"ressources/images/elements/" + index.data().toString());
    hideProperties();
    modifyTitle(true);
}

void SFMLCanvas::on_obstaclesListView_clicked(QModelIndex index) {
    _clicked = true;
    _currentItem = _items->add(3, "ressources/images/obstacles/" + index.data().toString());
    hideProperties();
    modifyTitle(true);
}

void SFMLCanvas::on_backgroundsListView_clicked(QModelIndex index) {
    _back_path = index.data().toString();
    _back_image.LoadFromFile("ressources/images/backgrounds/" + index.data().toString().toStdString());
    _back_sprite.SetImage(_back_image);
    _back_sprite.Resize(GetWidth(), GetHeight());
    hideProperties();
    modifyTitle(true);
}

void SFMLCanvas::on_refreshButton_clicked() {
    refreshItemsList();
}

void SFMLCanvas::on_angleEdit_sliderMoved(int position) {
    _items->setRotation(_currentItem, position);
    modifyTitle(true);
}

void SFMLCanvas::on_deleteButton_clicked() {
    _items->remove(_currentItem);
    hideProperties();
    modifyTitle(true);
}

void SFMLCanvas::on_limiteEdit_valueChanged(int value) {
    _limite_sprite.SetY(_base_sprite.GetPosition().y - value);
    modifyTitle(true);
}

void SFMLCanvas::on_typeEdit_currentIndexChanged(QString type) {
    _items->setType(_currentItem, type);
    modifyTitle(true);
}

void SFMLCanvas::on_loadMap() {
    loadMap();
}

void SFMLCanvas::on_saveAsMap() {
    saveAsMap();
}

void SFMLCanvas::on_saveMap() {
    saveMap();
}

void SFMLCanvas::on_close() {
    this->parentWidget()->close();
}

void SFMLCanvas::on_newMap() {
    newMap();
}
