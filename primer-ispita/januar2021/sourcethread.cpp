#include "sourcethread.h"
#include "source.h"

#include <QRandomGenerator>
#include <QMutexLocker>

SourceThread::SourceThread(QVector<Source *> sources, QMutex *mutex, QObject *parent)
    :QThread(parent)
    , m_sources(sources)
    , m_mutex(mutex)
{

}

void SourceThread::run()
{
    for(;;)
    {

        const auto ms = (QRandomGenerator::global()->generate() % 6)*100u + 500u;
        msleep(ms);
        const auto index = QRandomGenerator::global()->generate() % m_sources.size();
        const auto fluidLeft = m_sources[index]->volume();
        if (fluidLeft == 0u){
            continue;
        }

        QMutexLocker lock(m_mutex);


        const auto fluidLost = qMin(fluidLeft, QRandomGenerator::global()->generate() % 100 + 100); // izmedju 100 i 200
        m_sources[index]->runOut(fluidLost);

        emit sourceLostFluid(fluidLost);

        if(m_sources[index]->volume() == 0u){
            break;
        }
    }
}
