#include "SFMLCanvas.h"

SFMLCanvas::SFMLCanvas(QWidget* Parent, Ui::MainWindow& u, const QPoint& Position, const QSize& Size)
 : QSFMLCanvas(Parent, Position, Size), _clicked(false)
{
    _win = &u;
    connect(_win->BaseButton, SIGNAL(clicked()), this, SLOT(on_BaseButton_clicked()));
    connect(_win->elementsListView, SIGNAL(clicked(QModelIndex)), this, SLOT(on_elementsListView_clicked(QModelIndex)));

    _items = new ItemFactory("ressources/images/elements");
    _items->getList(*_win->elementsListView, 1);
    _items->setPath("ressources/images/obstacles");
    _items->getList(*_win->obstaclesListView, 2);
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

void SFMLCanvas::mouseReleaseEvent  ( QMouseEvent * e ) {
    if (e->x() >= (_base_sprite.GetPosition().x - _base_image.GetWidth()/2) && e->x() <= (_base_sprite.GetPosition().x - _base_image.GetWidth()/2 + _base_image.GetWidth())
        && e->y() >= (_base_sprite.GetPosition().y - _base_image.GetHeight()/2) && e->y() <= (_base_sprite.GetPosition().y - _base_image.GetHeight()/2 + _base_image.GetHeight())) {
        _mode = 1;
        displayProperties();
    } else {
        _win->objectProperties->setVisible(false);
    }
    _clicked = false;
}

void SFMLCanvas::OnUpdate() {
    Clear(sf::Color(255, 255, 255));
    Draw(_base_sprite);

    if (_clicked) {
        sp_curs.SetPosition(QCursor::pos().x() - 150 - curs.GetWidth()/2, QCursor::pos().y() - 100 - curs.GetHeight()/2);
        Draw(sp_curs);
    }
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

void SFMLCanvas::on_elementsListView_clicked(QModelIndex index) {
    std::cout << _items->getFile(index.row(), 1).toStdString() << std::endl;
    curs.LoadFromFile(_items->getFile(index.row(), 1).toStdString());
    sp_curs.SetImage(curs);
    _clicked = true;
}
