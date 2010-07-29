#ifndef SFMLCANVAS_H
#define SFMLCANVAS_H
#include "QSFMLCanvas.hpp"
#include <iostream>
#include "ui_main.h"
#include <QtCore>
#include "Item/ItemFactory.h"
#include <QListView>
#include <QStringListModel>
#include <QMouseEvent>

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
            void refreshItemsList();
            void mouseReleaseEvent( QMouseEvent * e );
            void keyPressEvent(QKeyEvent *key);
            sf::Image  _base_image;
            sf::Sprite _base_sprite;
            sf::Image _back_image;
            sf::Sprite _back_sprite;
            sf::Image _limite_image;
            sf::Sprite _limite_sprite;
            Ui::MainWindow *_win;
            int _mode;
            ItemFactory *_items;
            bool _clicked;
            int _currentItem;
            QString _back_path;

    private slots:
        void on_limiteEdit_valueChanged(int );
        void on_backgroundsListView_clicked(QModelIndex index);
        void on_deleteButton_clicked();
        void on_angleEdit_sliderMoved(int position);
        void on_refreshButton_clicked();
        void on_obstaclesListView_clicked(QModelIndex index);
        void on_elementsListView_clicked(QModelIndex index);
        void on_BaseButton_clicked();
};
#endif // SFMLCANVAS_H
