#ifndef SOURCETHREAD_H
#define SOURCETHREAD_H

#include <QThread>
#include <QMutex>

class Source;

class SourceThread : public QThread
{
    Q_OBJECT
public:
    explicit SourceThread(QVector<Source *> sources, QMutex *mutex, QObject *parent = nullptr);

protected:
    void run() override;

signals:
    void sourceLostFluid(unsigned fluidLost);

private:
    QVector<Source *> m_sources;
    QMutex *m_mutex;
};

#endif // SOURCETHREAD_H
