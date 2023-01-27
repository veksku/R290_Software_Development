#include "../inc/skaliranje.hpp"

namespace snap {
    skaliranje::skaliranje(const bool cuva_odnos_ivica, const bool prema_vecoj_ivici, const std::pair<unsigned, unsigned> &dimenzije)
        : cuva_odnos_ivica(cuva_odnos_ivica), prema_vecoj_ivici(prema_vecoj_ivici), dimenzije(dimenzije) {
            std::cout << "SKALIRANJE :: SKALIRANJE" << std::endl
                      << "SKALIRANJE :: SKALIRANJE :: CUVA ODNOS IVICA :: " << this->cuva_odnos_ivica << std::endl
                      << "SKALIRANJE :: SKALIRANJE :: PREMA VECOJ IVICI :: " << this->prema_vecoj_ivici << std::endl
                      << "SKALIRANJE :: SKALIRANJE :: DIMENZIJE :: (" << this->dimenzije.first << ", " << this->dimenzije.second << ")" << std::endl;
    }

    std::shared_ptr<Slika> skaliranje::primeni(std::shared_ptr<Slika> slika) const {
        slika->skaliraj(cuva_odnos_ivica, prema_vecoj_ivici, dimenzije);

        std::cout << "SKALIRANJE :: PRIMENI" << std::endl
                  << "SKALIRANJE :: PRIMENI :: CUVA ODNOS IVICA :: " << this->cuva_odnos_ivica << std::endl
                  << "SKALIRANJE :: PRIMENI :: PREMA VECOJ IVICI :: " << this->prema_vecoj_ivici << std::endl
                  << "SKALIRANJE :: PRIMENI :: DIMENZIJE :: (" << this->dimenzije.first << ", " << this->dimenzije.second << ")" << std::endl;

        return slika;
    }

    QVariant skaliranje::dohvati_stanje() const {
        QVariantMap map;

        map.insert("tip", "skaliranje");
        map.insert("cuva_odnos_ivica", cuva_odnos_ivica);
        map.insert("prema_vecoj_ivici", prema_vecoj_ivici);
        map.insert("dimenzije.first", this->dimenzije.first);
        map.insert("dimenzije.second", this->dimenzije.second);

        std::cout << "SKALIRANJE :: STANJE" << std::endl
                  << "SKALIRANJE :: STANJE :: CUVA ODNOS IVICA :: " << map["cuva_odnos_ivica"].toBool() << std::endl
                  << "SKALIRANJE :: STANJE :: PREMA VECOJ IVICI :: " << map["prema_vecoj_ivici"].toBool() << std::endl
                  << "SKALIRANJE :: STANJE :: DIMENZIJE :: (" << map["dimenzije.first"].toUInt() << ", " << map["dimenzije.second"].toUInt() << ")" << std::endl;

        return map;
    }
}
