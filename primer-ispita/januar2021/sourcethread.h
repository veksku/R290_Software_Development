#ifndef SOURCETHREAD_H
#define SOURCETHREAD_H

#include <QThread>
#include <QObject>
#include <QVector>
#include <QMutex>

class Source;

class SourceThread : public QThread
{
    Q_OBJECT
public:
    explicit SourceThread(QVector<Source *> izvori, QMutex *mutex, QObject *parent = nullptr);

protected:
    void run() override;

signals:
    void signalST(unsigned fluidLost);

private:
    QVector<Source *> m_izvori;
    QMutex *m_mutex;
};

#endif // SOURCETHREAD_H
