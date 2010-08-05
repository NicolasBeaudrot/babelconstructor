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
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QtXml>

    class SFMLCanvas : public QSFMLCanvas
    {
        Q_OBJECT

        public :
            SFMLCanvas(QWidget* Parent, Ui::MainWindow& u, const QPoint& Position, const QSize& Size);
            ~SFMLCanvas();
            void displayProperties();
            void hideProperties();
            void loadMap(QString file);

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
        void on_restitutionEdit_valueChanged(double );
        void on_frictionEdit_valueChanged(double );
        void on_densityEdit_valueChanged(double );
        void on_widthEdit_valueChanged(double );
        void on_loadButton_clicked();
        void on_typeEdit_currentIndexChanged(QString );
        void on_saveButton_clicked();
        void on_limiteEdit_valueChanged(int );
        void on_backgroundsListView_clicked(QModelIndex index);
        void on_deleteButton_clicked();
        void on_angleEdit_sliderMoved(int position);
        void on_refreshButton_clicked();
        void on_obstaclesListView_clicked(QModelIndex index);
        void on_elementsListView_clicked(QModelIndex index);
};
#endif // SFMLCANVAS_H
