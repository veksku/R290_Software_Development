#include "sourcethread.h"
#include "source.h"

#include <QRandomGenerator>
#include <QMutexLocker>

SourceThread::SourceThread(QVector<Source *> izvori, QMutex *mutex, QObject *parent)
    :QThread(parent)
    , m_izvori(izvori)
    , m_mutex(mutex)
{
}

void SourceThread::run()
{
    for(;;){
        const auto ms = (QRandomGenerator::global()->generate() % 6) * 100u + 500u;
        msleep(ms);
        const auto index = QRandomGenerator::global()->generate() % m_izvori.size();
        const auto fluidLeft = m_izvori[index]->zapremina();
        if (fluidLeft == 0)
            continue;

        QMutexLocker lock(m_mutex);

        const auto fluidLost = qMin(fluidLeft, QRandomGenerator::global()->generate() % 100 + 100u);
        m_izvori[index]->runOut(fluidLost);

        emit signalST(fluidLost);

        if(m_izvori[index]->zapremina() == 0)
            break;
    }
}
