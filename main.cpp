# include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    win w;
    w.show();
    return app.exec();
}