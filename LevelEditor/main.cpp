#include <Qt/qapplication.h>
#include <Qt/qframe.h>
#include "Canvas/SFMLCanvas.h"
#include "ui_main.h"

int main(int argc, char **argv)
{
    QApplication App(argc, argv);

    // On crée la fenêtre principale
    QFrame* MainFrame = new QFrame;
    Ui::MainWindow ui;
    ui.setupUi(MainFrame);
    MainFrame->setWindowTitle("Babel Level Editor");

    //On crée une vue SFML dans la fenêtre principale
    SFMLCanvas* SFMLView = new SFMLCanvas(MainFrame, ui, QPoint(150, 40), QSize(800, 600));

    MainFrame->setWindowState(Qt::WindowMaximized);
    MainFrame->show();
    SFMLView->show();

    return App.exec();
}
