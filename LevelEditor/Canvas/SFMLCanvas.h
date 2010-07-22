#ifndef SFMLCANVAS_H
#define SFMLCANVAS_H
#include "QSFMLCanvas.hpp"
#include <QMouseEvent>
#include <vector>
#include <iostream>
#include "ui_main.h"
#include "Item/ItemFactory.h"

    class SFMLCanvas : public QSFMLCanvas
    {
        Q_OBJECT

        public :
            SFMLCanvas(QWidget* Parent, Ui::MainWindow& u, const QPoint& Position, const QSize& Size);
            ~SFMLCanvas();
            void displayProperties();
            void hideProperties();

        private :
            void OnInit();
            void OnUpdate();
            void mouseReleaseEvent( QMouseEvent * e );
            sf::Image  _base_image;
            sf::Sprite _base_sprite;
            sf::Image curs;
            sf::Sprite sp_curs;
            Ui::MainWindow *_win;
            int _mode;
            ItemFactory *_items;
            bool _clicked;

    private slots:
        void on_elementsListView_clicked(QModelIndex index);
        void on_BaseButton_clicked();
};
#endif // SFMLCANVAS_H
