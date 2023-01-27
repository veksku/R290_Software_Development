#include "../inc/CuvarSlike.hpp"

namespace snap {
    CuvarSlike::CuvarSlike(const std::string &putanja)
        : element(0), _putanja(putanja), _original(std::make_shared<Slika>(putanja)) {
            std::cout << "CUVAR SLIKE :: CUVAR SLIKE" << std::endl
                      << "CUVAR SLIKE :: CUVAR SLIKE :: PUTANJA :: " << this->_putanja << std::endl;
        }

    std::shared_ptr<Slika> CuvarSlike::primeni() const {
        std::cout << "CUVAR SLIKE :: PRIMENI" << std::endl;

        return std::make_shared<Slika>(_original);
    }

    std::shared_ptr<Slika> CuvarSlike::primeni(std::shared_ptr<Slika> slika) const {
        return element::primeni(slika);
    }
    
    std::shared_ptr<Slika> CuvarSlike::primeni(std::shared_ptr<Slika> prva_slika, std::shared_ptr<Slika> druga_slika) const {
        return element::primeni(prva_slika, druga_slika);
    }

    QVariant CuvarSlike::dohvati_stanje() const {
        QVariantMap map;

        map.insert("tip", "cuvar_slike");
        map.insert("putanja", _putanja.c_str());

        std::cout << "CUVAR SLIKE :: STANJE" << std::endl
                  << "CUVAR SLIKE :: STANJE :: PUTANJA :: " << map["putanja"].toString().toStdString() << std::endl;

        return map;
    }
}
