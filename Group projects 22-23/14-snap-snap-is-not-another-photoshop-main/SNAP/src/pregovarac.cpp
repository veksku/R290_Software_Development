#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QRandomGenerator>
#include <QTextStream>
#include "../inc/pregovarac.hpp"

Pregovarac::Pregovarac(QWidget *parent)
    : QWidget{parent}
{
}

unsigned Pregovarac::createImg(QString imgPath)
{
    tmpId = Proizvodjac_Projektant.dodaj_sliku(imgPath.toStdString());
    return tmpId;

}

QImage* Pregovarac::toQImage(Magick::Image image)
{
    QImage *newQImage = new QImage(image.columns(), image.rows(), QImage::Format_RGB32);

    const Magick::PixelPacket *pixels = nullptr;
    Magick::ColorRGB rgb;
    for (int y = 0; y < newQImage->height(); y++) {
        pixels = image.getConstPixels(0, y, newQImage->width(), 1);
        for (int x = 0; x < newQImage->width(); x++) {
            rgb = (*(pixels + x));
            newQImage->setPixel(x, y, QColor((int) (255 * rgb.red())
                                             , (int) (255 * rgb.green())
                                             , (int) (255 * rgb.blue())).rgb());
        }
    }
    return newQImage;
}

QImage *Pregovarac::showCurrentImg(unsigned broj_slike)
{
    return toQImage(Proizvodjac_Projektant.uradi_sliku(broj_slike)->dohvati_sliku());
}

unsigned Pregovarac::CropImage(const unsigned int A_x, const unsigned int A_y, const unsigned int B_x, const unsigned int B_y, unsigned id_ulaza)
{
    return Proizvodjac_Projektant.dodaj_isecanje(std::make_pair(A_x, A_y), std::make_pair(B_x, B_y), id_ulaza);
}

unsigned Pregovarac::ScaleImage(const bool cuva_odnos_ivica, const bool prema_vecoj_ivici, const std::pair<unsigned int, unsigned int> &dimenzije, unsigned id_ulaza)
{
    return Proizvodjac_Projektant.dodaj_skaliranje(cuva_odnos_ivica, prema_vecoj_ivici, dimenzije, id_ulaza);
}

unsigned Pregovarac::mergeImage(const bool horizontalno, const bool obrnutim_redosledom, const Poravnanje poravnanje, const std::string boja_pozadine, const std::optional<unsigned int> id_prvog_ulaza, const std::optional<unsigned int> id_drugog_ulaza)
{
    return Proizvodjac_Projektant.dodaj_spajanje(horizontalno, obrnutim_redosledom, poravnanje, boja_pozadine, id_prvog_ulaza, id_drugog_ulaza);
}

unsigned int Pregovarac::EnhanceImg(unsigned int id_ulaza)
{
    return Proizvodjac_Projektant.dodaj_enhance(id_ulaza);
}

void Pregovarac::changeImage(const unsigned int id, QString &putanja)
{
    Proizvodjac_Projektant.promeni_sliku(id, putanja.toStdString());
}

void Pregovarac::changeCrop(const unsigned int id, const unsigned int A_x, const unsigned int A_y, const unsigned int B_x, const unsigned int B_y)
{
    Proizvodjac_Projektant.promeni_isecanje(id, std::make_pair(A_x, A_y), std::make_pair(B_x, B_y));
}

void Pregovarac::changeScale(const unsigned int id, const bool cuva_odnos_ivica, const bool prema_vecoj_ivici, const std::pair<unsigned int, unsigned int> &dimenzije)
{
    Proizvodjac_Projektant.promeni_skaliranje(id, cuva_odnos_ivica, prema_vecoj_ivici, dimenzije);
}

void Pregovarac::changeMerge(const unsigned int id, const bool horizontalno, const bool obrnutim_redosledom, const Poravnanje poravnanje, const std::string boja_pozadine)
{
    Proizvodjac_Projektant.promeni_spajanje(id, horizontalno, obrnutim_redosledom, poravnanje, boja_pozadine);
}

void Pregovarac::removeElement(const unsigned int id)
{
    Proizvodjac_Projektant.obrisi_element(id);
}


bool Pregovarac::loadProject(QString projectPath)
{
    QFile loadFile(projectPath);

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QVariant stanje = loadDoc.toVariant();

    Proizvodjac_Projektant.postavi_stanje(stanje);

    const QVariantList &lista = stanje.toList();

        for(const QVariant &var : lista) {
            const QVariantMap &mapa = var.toMap();

            unsigned id = mapa["id"].toUInt();

            if(mapa["tip"] == "enhance") {
                element_state[id] = "Enhance";
                if(!mapa["ulaz"].isNull())
                    ulazi[id] = mapa["ulaz"].toUInt();
            }
            else if(mapa["tip"] == "isecanje") {
                element_state[id] = "Crop";
                if(!mapa["ulaz"].isNull())
                    ulazi[id] = mapa["ulaz"].toUInt();
            }
            else if(mapa["tip"] == "skaliranje") {
                element_state[id] = "Scale";
                if(!mapa["ulaz"].isNull())
                    ulazi[id] = mapa["ulaz"].toUInt();
            }
            else if(mapa["tip"] == "spajanje") {
                element_state[id] = "Merge";
                if(!mapa["ulaz2"].isNull())
                    ulazi[id] = mapa["ulaz"].toUInt();
            }
            else if(mapa["tip"] == "cuvar_slike") {
                element_state[id] = "Image";
            }
        }

    return true;
}

bool Pregovarac::saveProject(QString projectPath) const
{
    QVariant stanje = Proizvodjac_Projektant.dohvati_stanje();

    QFile saveFile(projectPath);

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QJsonDocument saveDoc = QJsonDocument::fromVariant(stanje);
    saveFile.write(saveDoc.toJson());

    return true;
}

bool Pregovarac::saveImage(QString imgPath, const unsigned broj_slike)
{
    QImage* img = toQImage(Proizvodjac_Projektant.uradi_sliku(broj_slike)->dohvati_sliku());
    img->save(imgPath);
    return true;
}

std::map<unsigned int, QString> Pregovarac::getElement_state() const
{
    return element_state;
}

std::map<unsigned int, unsigned int> Pregovarac::getUlazi() const
{
    return ulazi;
}
