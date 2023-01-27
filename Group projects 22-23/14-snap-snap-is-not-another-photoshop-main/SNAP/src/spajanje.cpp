#include "../inc/spajanje.hpp"

namespace snap {
    spajanje::spajanje(const bool horizontalno, const bool obrnutim_redosledom, const Poravnanje &poravnanje, const std::string boja_pozadine)
        : horizontalno(horizontalno), obrnutim_redosledom(obrnutim_redosledom), poravnanje(poravnanje), boja_pozadine(boja_pozadine) {
            std::cout << "SPAJANJE :: SPAJANJE" << std::endl
                      << "SPAJANJE :: SPAJANJE :: HORIZONTALNO :: " << this->horizontalno << std::endl
                      << "SPAJANJE :: SPAJANJE :: OBRNUTIM REDOSLEDOM :: " << this->obrnutim_redosledom << std::endl
                      << "SPAJANJE :: SPAJANJE :: PORAVNANJE :: " << poravnanje_to_string(this->poravnanje) << std::endl
                      << "SPAJANJE :: SPAJANJE :: BOJA POZADINE :: " << this->boja_pozadine << std::endl;
    }

    std::shared_ptr<Slika> spajanje::primeni(std::shared_ptr<Slika> prva_slika, std::shared_ptr<Slika> druga_slika) const {
        std::cout << "SPAJANJE :: PRIMENI" << std::endl
                  << "SPAJANJE :: PRIMENI :: HORIZONTALNO :: " << this->horizontalno << std::endl
                  << "SPAJANJE :: PRIMENI :: OBRNUTIM REDOSLEDOM :: " << this->obrnutim_redosledom << std::endl
                  << "SPAJANJE :: PRIMENI :: PORAVNANJE :: " << poravnanje_to_string(this->poravnanje) << std::endl
                  << "SPAJANJE :: PRIMENI :: BOJA POZADINE :: " << this->boja_pozadine << std::endl;

        if(!this->obrnutim_redosledom) {
            prva_slika->zalepi(druga_slika, horizontalno, poravnanje, boja_pozadine);
            return prva_slika;
        }
        else {
            druga_slika->zalepi(prva_slika, horizontalno, poravnanje, boja_pozadine);
            return druga_slika;
        }
    }

    QVariant spajanje::dohvati_stanje() const {
        QVariantMap map;

        map.insert("tip", "spajanje");
        map.insert("horizontalno", horizontalno);
        map.insert("obrnutim_redosledom", obrnutim_redosledom);
        map.insert("poravnanje", poravnanje_to_string(poravnanje).c_str());
        map.insert("boja_pozadine", boja_pozadine.c_str());

        std::cout << "SPAJANJE :: STANJE" << std::endl
                  << "SPAJANJE :: STANJE :: HORIZONTALNO :: " << map["horizontalno"].toBool() << std::endl
                  << "SPAJANJE :: STANJE :: OBRNUTIM REDOSLEDOM :: " << map["obrnutim_redosledom"].toBool() << std::endl
                  << "SPAJANJE :: STANJE :: PORAVNANJE :: " << map["poravnanje"].toString().toStdString() << std::endl
                  << "SPAJANJE :: STANJE :: BOJA POZADINE :: " << map["boja_pozadine"].toString().toStdString() << std::endl;

        return map;
    }
}
