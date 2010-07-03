#ifndef SFMLCANVAS_H
#define SFMLCANVAS_H
#include "QSFMLCanvas.hpp"

    class SFMLCanvas : public QSFMLCanvas
    {
        public :
            SFMLCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size);

        private :
            void OnInit();
            void OnUpdate();
            sf::Image  myImage;
            sf::Sprite mySprite;
    };
#endif // SFMLCANVAS_H
