#include "source.h"

Source::Source()
{

}

void Source::fromQVariant(const QVariant &variant)
{
    const auto map = variant.toMap();

    m_name = map.value("name").toString();
    m_volume = map.value("volume").toUInt();
}

QString Source::toQString() const
{
    return m_name + " - " + (m_volume == 0u ? "izvor je iscrpljen" : QString::number(m_volume));
}

void Source::runOut(unsigned int fluidLost)
{
    m_volume -= fluidLost; //ne mora provera jer se ona vrsi u niti ranije
}
