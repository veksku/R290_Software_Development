#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMutex>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Source;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void onFillSources();
    void onStartTransfer();
    void onSourceLostFluid(unsigned lostFluid);

private:
    bool deserializeSources();
    void showSources();
    void showTotalVolume();

private:
    Ui::Widget *ui;
    QVector<Source *> m_sources;
    QMutex m_mutex;
};
#endif // WIDGET_H
