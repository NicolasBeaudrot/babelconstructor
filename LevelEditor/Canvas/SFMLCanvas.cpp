#include "SFMLCanvas.h"

SFMLCanvas::SFMLCanvas(QWidget* Parent, Ui::MainWindow& u, const QPoint& Position, const QSize& Size)
 : QSFMLCanvas(Parent, Position, Size)
{
    _win = &u;
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
        _win->objectProperties->setVisible(true);
        _win->objectProperties->setTitle("Properties : Base");
    } else {
        _win->objectProperties->setVisible(false);
    }
}

void SFMLCanvas::OnUpdate() {

    Clear(sf::Color(255, 255, 255));

    Draw(_base_sprite);


}

