#include "SFMLCanvas.h"

SFMLCanvas::SFMLCanvas(QWidget* Parent, Ui::MainWindow& u, const QPoint& Position, const QSize& Size)
 : QSFMLCanvas(Parent, Position, Size)
{
    _win = &u;
    connect(_win->BaseButton, SIGNAL(clicked()), this, SLOT(on_BaseButton_clicked()));
    connect(_win->elementsListView, SIGNAL(clicked(QModelIndex)), this, SLOT(on_listView_clicked(QModelIndex)));

    _elements = new ItemFactory("ressources/images/elements");
    _elements->getList(*_win->elementsListView);
    _obstacles = new ItemFactory("ressources/images/obstacles");
    _obstacles->getList(*_win->obstaclesListView);
}

SFMLCanvas::~SFMLCanvas() {
    delete _elements;
    delete _obstacles;
}

void SFMLCanvas::OnInit() {
    _win->objectProperties->setVisible(false);

    //First we load the base
    _base_image.LoadFromFile("ressources/images/barre.png");
    _base_sprite.SetImage(_base_image);
    _base_sprite.SetCenter(_base_sprite.GetSize() / 2.0f);
    _base_sprite.SetPosition(this->GetWidth()/2, this->GetHeight()-50);
}

void SFMLCanvas::mouseReleaseEvent  ( QMouseEvent * e ) {
    if (e->x() >= (_base_sprite.GetPosition().x - _base_image.GetWidth()/2) && e->x() <= (_base_sprite.GetPosition().x - _base_image.GetWidth()/2 + _base_image.GetWidth())
        && e->y() >= (_base_sprite.GetPosition().y - _base_image.GetHeight()/2) && e->y() <= (_base_sprite.GetPosition().y - _base_image.GetHeight()/2 + _base_image.GetHeight())) {
        _mode = 1;
        displayProperties();
    } else {
        _win->objectProperties->setVisible(false);
    }
}

void SFMLCanvas::OnUpdate() {
    Clear(sf::Color(255, 255, 255));
    Draw(_base_sprite);
}

void SFMLCanvas::on_BaseButton_clicked() {
    if (_mode == 1) {
        _base_sprite.Resize(_win->widthEdit->text().toFloat(), _base_image.GetHeight());
    }
}

void SFMLCanvas::displayProperties() {
    hideProperties();

    switch(_mode) {
        case 1 : { //Mode base
            _win->objectProperties->setTitle("Properties : Base");
            _win->widthLabel->setVisible(true);
            _win->widthEdit->setVisible(true);
            QString width;
            _win->widthEdit->setText(width.setNum(_base_image.GetWidth()));
        }
        break;

        case 2 : { //Mode Elements
            _win->objectProperties->setTitle("Properties : Element");
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

void SFMLCanvas::on_listView_clicked(QModelIndex index)
{
    std::cout << "Index : " << index.row() << std::endl;
}
