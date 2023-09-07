#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QMutex>

class Source;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void showSources();
    void showVolume();
    bool deserialize();
    bool deserialize2();
    bool deserialize3();

public slots:
    void onFillSources();
    void onStartTransfer();
    void onSourceLostFluid(unsigned lostFluid);

private:
    Ui::MainWindow *ui;
    QVector<Source *> m_izvori;
    QMutex m_mutex;
};
#endif // MAINWINDOW_H
