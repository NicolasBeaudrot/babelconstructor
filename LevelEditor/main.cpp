#include <Qt/qapplication.h>
#include <Qt/qframe.h>
#include "Canvas/SFMLCanvas.h"

int main(int argc, char **argv)
{
    QApplication App(argc, argv);

    // On crée la fenêtre principale
    QFrame* MainFrame = new QFrame;
    MainFrame->setWindowTitle("Babel Level Editor");
    MainFrame->resize(400, 400);
    MainFrame->show();

    //On crée une vue SFML dans la fenêtre principale
    SFMLCanvas* SFMLView = new SFMLCanvas(MainFrame, QPoint(20, 20), QSize(360, 360));
    SFMLView->show();

    return App.exec();
}
