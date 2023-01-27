#ifndef PREGOVARAC_HPP
#define PREGOVARAC_HPP

#include <memory>
#include <QObject>
#include <QWidget>
#include <QJsonObject>
#include "slika.hpp"
#include "proizvodjac_projektant.hpp"

class Pregovarac : public QWidget
{
    Q_OBJECT
public:
    explicit Pregovarac(QWidget *parent = nullptr);
    unsigned createImg(QString imgPath);
    QImage* toQImage(Magick::Image image);
    QImage* showCurrentImg(unsigned broj_slike);

    unsigned CropImage(const unsigned A_x, const unsigned A_y, const unsigned B_x, const unsigned B_y, unsigned id_ulaza);
    unsigned ScaleImage(const bool cuva_odnos_ivica, const bool prema_vecoj_ivici, const std::pair<unsigned, unsigned> &dimenzije, unsigned id_ulaza);
    unsigned mergeImage(const bool horizontalno, const bool obrnutim_redosledom, const Poravnanje poravnanje, const std::string boja_pozadine, const std::optional<unsigned> id_prvog_ulaza = std::nullopt, const std::optional<unsigned> id_drugog_ulaza = std::nullopt);
    unsigned EnhanceImg(unsigned id_ulaza);

    void changeImage(const unsigned id, QString &putanja);
    void changeCrop(const unsigned id, const unsigned A_x, const unsigned A_y, const unsigned B_x, const unsigned B_y);
    void changeScale(const unsigned id, const bool cuva_odnos_ivica, const bool prema_vecoj_ivici, const std::pair<unsigned, unsigned> &dimenzije);
    void changeMerge(const unsigned id, const bool horizontalno, const bool obrnutim_redosledom, const Poravnanje poravnanje, const std::string boja_pozadine);

    void removeElement(const unsigned id);

    bool loadProject(QString projectPath);
    bool saveProject(QString projectPath) const;
    bool saveImage(QString imgPath, const unsigned broj_slike);

    std::map<unsigned int, QString> getElement_state() const;
    std::map<unsigned int, unsigned int> getUlazi() const;

    std::shared_ptr<snap::GotovaSlika> currentImg;
    unsigned tmpId;

private:
    snap::proizvodjac_projektant Proizvodjac_Projektant;
    std::map<unsigned, QString> element_state;
    std::map<unsigned, unsigned> ulazi;

signals:

};

#endif // PREGOVARAC_HPP
