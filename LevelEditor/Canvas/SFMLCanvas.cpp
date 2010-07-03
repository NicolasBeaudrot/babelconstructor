#include "SFMLCanvas.h"

SFMLCanvas::SFMLCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size)
 : QSFMLCanvas(Parent, Position, Size)
{

}

void SFMLCanvas::OnInit() {
    // On charge une image
    myImage.LoadFromFile("ressources/images/barre.png");

    // On paramètre le sprite
    mySprite.SetImage(myImage);
    mySprite.SetCenter(mySprite.GetSize() / 2.f);
    mySprite.SetPosition(50,100);

}

void SFMLCanvas::OnUpdate() {

    // On efface l'écran
    Clear(sf::Color(255, 255, 255));

    // Et on l'affiche
    Draw(mySprite);
}

