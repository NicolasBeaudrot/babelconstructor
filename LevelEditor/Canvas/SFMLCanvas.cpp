#include "SFMLCanvas.h"

SFMLCanvas::SFMLCanvas(QWidget* Parent, Ui::MainWindow& u, const QPoint& Position, const QSize& Size)
 : QSFMLCanvas(Parent, Position, Size), _clicked(false)
{
    _win = &u;
    connect(_win->BaseButton, SIGNAL(clicked()), this, SLOT(on_BaseButton_clicked()));
    connect(_win->elementsListView, SIGNAL(clicked(QModelIndex)), this, SLOT(on_elementsListView_clicked(QModelIndex)));
    connect(_win->obstaclesListView, SIGNAL(clicked(QModelIndex)), this, SLOT(on_obstaclesListView_clicked(QModelIndex)));
    connect(_win->refreshButton, SIGNAL(clicked()), this, SLOT(on_refreshButton_clicked()));
    connect(_win->angleEdit, SIGNAL(sliderMoved(int)), this, SLOT(on_angleEdit_sliderMoved(int)));
    connect(_win->deleteButton, SIGNAL(clicked()), this, SLOT(on_deleteButton_clicked()));
    connect(_win->backgroundsListView, SIGNAL(clicked(QModelIndex)), this, SLOT(on_backgroundsListView_clicked(QModelIndex)));
    connect(_win->limiteEdit, SIGNAL(valueChanged(int)), this, SLOT(on_limiteEdit_valueChanged(int)));
    connect(_win->saveButton, SIGNAL(clicked()), this, SLOT(on_saveButton_clicked()));
    connect(_win->typeEdit, SIGNAL(currentIndexChanged(QString)), this, SLOT(on_typeEdit_currentIndexChanged(QString)));
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
    _limite_sprite.SetPosition(this->GetWidth() - _limite_image.GetWidth(), this->GetHeight() - _win->limiteEdit->text().toFloat());
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
    Draw(_back_sprite);
    Draw(_base_sprite);
    Draw(_limite_sprite);

    if (_clicked) {
        _items->setPosition(_currentItem, sf::Vector2f(QCursor::pos().x() - 150, QCursor::pos().y() - 80));
    }
    _items->render(*this);
}

void SFMLCanvas::on_BaseButton_clicked() {
    if (_mode == 1) { //Base
        _base_sprite.Resize(_win->widthEdit->text().toFloat(), _base_image.GetHeight());
    } else if (_mode == 2) { //Element
        float prop[8];
        prop[2] = _win->xEdit->text().toFloat();
        prop[3] = _win->yEdit->text().toFloat();
        prop[4] = _win->angleEdit->value();
        prop[5] = _win->densityEdit->value();
        prop[6] = _win->frictionEdit->value();
        prop[7] = _win->restitutionEdit->value();
        _items->setProperties(_currentItem, prop);
        _items->setPosition(_currentItem, sf::Vector2f(prop[2], prop[3]));
    } else if (_mode == 3) { //Obstacle
        float prop[8];
        prop[2] = _win->xEdit->text().toFloat();
        prop[3] = _win->yEdit->text().toFloat();
        prop[4] = _win->angleEdit->value();
        prop[5] = 0.0f;
        prop[6] = 0.0f;
        prop[7] = 0.0f;
        _items->setProperties(_currentItem, prop);
        _items->setPosition(_currentItem, sf::Vector2f(prop[2], prop[3]));
    }
}

void SFMLCanvas::displayProperties() {
    hideProperties();

    switch(_mode) {
        case 1 : { //Mode base
            _win->objectProperties->setTitle("Properties : Base");
            _win->widthEdit->setEnabled(true);
            _win->widthLabel->setVisible(true);
            _win->widthEdit->setVisible(true);
            QString width;
            _win->widthEdit->setText(width.setNum(_base_image.GetWidth()));
        }
        break;
        case 2 : { //Mode Elements
            float *prop = _items->getProperties(_currentItem);
            QString s;
            _win->widthEdit->setText(s.setNum(prop[0]));
            _win->heightEdit->setText(s.setNum(prop[1]));
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
            _win->widthEdit->setText(s.setNum(prop[0]));
            _win->heightEdit->setText(s.setNum(prop[1]));
            _win->widthEdit->setEnabled(false);
            _win->heightEdit->setEnabled(false);
            _win->xEdit->setText(s.setNum(prop[2]));
            _win->yEdit->setText(s.setNum(prop[3]));
            _win->angleEdit->setValue(prop[4]);
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

void SFMLCanvas::on_elementsListView_clicked(QModelIndex index) {
    _clicked = true;
    _currentItem = _items->add(2,"ressources/images/elements/" + index.data().toString());
    hideProperties();
}

void SFMLCanvas::on_obstaclesListView_clicked(QModelIndex index) {
    _clicked = true;
    _currentItem = _items->add(3, "ressources/images/obstacles/" + index.data().toString());
    hideProperties();
}

void SFMLCanvas::on_refreshButton_clicked() {
    refreshItemsList();
}

void SFMLCanvas::on_angleEdit_sliderMoved(int position) {
    _items->setRotation(_currentItem, position);
}

void SFMLCanvas::on_deleteButton_clicked() {
    _items->remove(_currentItem);
    hideProperties();
}

void SFMLCanvas::on_backgroundsListView_clicked(QModelIndex index) {
    _back_path = index.data().toString();
    _back_image.LoadFromFile("ressources/images/backgrounds/" + index.data().toString().toStdString());
    _back_sprite.SetImage(_back_image);
    _back_sprite.Resize(GetWidth(), GetHeight());
    hideProperties();
}

void SFMLCanvas::on_limiteEdit_valueChanged(int value) {
    _limite_sprite.SetY(this->GetHeight() - value);
}

void SFMLCanvas::on_saveButton_clicked() {
    QString qs = QInputDialog::getText(this, "Save as", "Enter a filename :");

    if (!qs.isEmpty()) {
        QFile file("ressources/map/" + qs + ".xml");

        if (file.open(QFile::WriteOnly)) {
            QTextStream out(&file);
            out << "<?xml version=\"1.0\" ?>" << endl;
            out << "<map>" << endl;
            if (_back_path.isEmpty()) {
                _back_path = "empty";
            }
            out << "<background>" << _back_path << "</background>" << endl;
            out << "<support width=\"" << _base_image.GetWidth() << "\" height=\"" << _base_image.GetHeight() << "\">barre.png</support>" << endl;
            out << "<limite y=\"" << (_base_sprite.GetPosition().y - _limite_sprite.GetPosition().y) << "\">limite.png</limite>" << endl;
            out << _items->save(_base_sprite.GetPosition().x - _base_image.GetWidth()/2, _base_sprite.GetPosition().y - _base_image.GetHeight()/2) << endl;
            out << "</map>";
        }
    } else {
        QMessageBox msgBox;
        msgBox.setText("Incorrect filename");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
    }
}

void SFMLCanvas::on_typeEdit_currentIndexChanged(QString type) {
    _items->setType(_currentItem, type);
    std::cout << type.toStdString() << std::endl;
}
