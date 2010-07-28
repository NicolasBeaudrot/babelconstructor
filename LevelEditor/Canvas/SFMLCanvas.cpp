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
    _base_sprite.SetPosition(this->GetWidth()/2, this->GetHeight()-50);
}

void SFMLCanvas::refreshItemsList() {
    QStringList files = QDir( "ressources/images/elements" ).entryList(QDir::Files | QDir::NoDotAndDotDot);
    _win->elementsListView->setModel(new QStringListModel(files));
    files = QDir( "ressources/images/obstacles" ).entryList(QDir::Files | QDir::NoDotAndDotDot);
    _win->obstaclesListView->setModel(new QStringListModel(files));
}

void SFMLCanvas::mouseReleaseEvent  ( QMouseEvent * e ) {
    if (e->button() == Qt::LeftButton) {
        if (e->x() >= (_base_sprite.GetPosition().x - _base_image.GetWidth()/2) && e->x() <= (_base_sprite.GetPosition().x - _base_image.GetWidth()/2 + _base_image.GetWidth())
            && e->y() >= (_base_sprite.GetPosition().y - _base_image.GetHeight()/2) && e->y() <= (_base_sprite.GetPosition().y - _base_image.GetHeight()/2 + _base_image.GetHeight())) {
            _mode = 1;
            displayProperties();
        } else if (_items->isClicked(e->x(), e->y()) != -1) {
            _currentItem = _items->isClicked(e->x(), e->y());
            _mode = _items->getType(_currentItem);
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
    Clear(sf::Color(255, 255, 255));
    Draw(_base_sprite);

    if (_clicked) {
        _items->setPosition(_currentItem, sf::Vector2f(QCursor::pos().x() - 150, QCursor::pos().y() - 100));
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
        prop[6] = _win->restitutionEdit->value();
        prop[7] = _win->frictionEdit->value();
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
            _win->restitutionEdit->setValue(prop[6]);
            _win->frictionEdit->setValue(prop[7]);
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
            _win->objectProperties->setTitle("Properties : Obstacle");
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
}

void SFMLCanvas::on_elementsListView_clicked(QModelIndex index) {
    _clicked = true;
    _currentItem = _items->add(2,"ressources/images/elements/" + index.data().toString());
}

void SFMLCanvas::on_obstaclesListView_clicked(QModelIndex index)
{
    _clicked = true;
    _currentItem = _items->add(3, "ressources/images/obstacles/" + index.data().toString());
}

void SFMLCanvas::on_refreshButton_clicked()
{
    refreshItemsList();
}

void SFMLCanvas::on_angleEdit_sliderMoved(int position)
{
    _items->setRotation(_currentItem, position);
    std::cout << position << std::endl;
}
