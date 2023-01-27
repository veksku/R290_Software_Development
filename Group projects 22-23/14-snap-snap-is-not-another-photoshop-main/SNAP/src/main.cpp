#include "../inc/mainwindow.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Magick::InitializeMagick(nullptr);
    MainWindow w;
    w.show();
    return a.exec();
}
