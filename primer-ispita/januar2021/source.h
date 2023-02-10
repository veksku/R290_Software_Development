#ifndef SOURCE_H
#define SOURCE_H

#include <QString>
#include <QVariant>

class Source
{
public:
    Source();
    void fromQVariant(const QVariant &variant);
    QString toQString() const;

    inline unsigned volume() const{
        return m_volume;
    }

    void runOut(unsigned fluidLost);

private:
    QString m_name;
    unsigned m_volume;
};

#endif // SOURCE_H
