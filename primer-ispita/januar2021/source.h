#ifndef SOURCE_H
#define SOURCE_H

#include <QString>
#include <QVariant>

class Source
{
public:
    Source();
    void fromQVariant(const QVariant &variant);
    QString toQString();

    unsigned int zapremina() const;
    void runOut(const unsigned fluidLost);

private:
    QString m_naziv;
    unsigned m_zapremina;
};

#endif // SOURCE_H
