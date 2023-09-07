#include "source.h"



Source::Source()
{

}

void Source::fromQVariant(const QVariant &variant)
{
    const auto map = variant.toMap();

    m_naziv = map.value("name").toString();
    m_zapremina = map.value("volume").toUInt();
}

QString Source::toQString()
{
    return m_naziv + " - " + (m_zapremina == 0u ? "izvor je iscrpljen" : QString::number(m_zapremina));
}

unsigned int Source::zapremina() const
{
    return m_zapremina;
}

void Source::runOut(const unsigned int fluidLost)
{
    m_zapremina -= fluidLost;
}
