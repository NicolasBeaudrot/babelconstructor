#ifndef SFMLCANVAS_H
#define SFMLCANVAS_H
#include "QSFMLCanvas.hpp"
#include <QMouseEvent>
#include <vector>
#include <iostream>
#include "ui_main.h"

    class SFMLCanvas : public QSFMLCanvas
    {
        public :
            SFMLCanvas(QWidget* Parent, Ui::MainWindow& u, const QPoint& Position, const QSize& Size);

        private :
            void OnInit();
            void OnUpdate();
            void mouseReleaseEvent( QMouseEvent * e );
            sf::Image  _base_image;
            sf::Sprite _base_sprite;

            Ui::MainWindow *_win;
    };
#endif // SFMLCANVAS_H
