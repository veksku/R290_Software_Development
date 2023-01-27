#include "../inc/isecanje.hpp"

namespace snap {
    isecanje::isecanje(const std::pair<unsigned, unsigned> &gornja_leva_tacka, const std::pair<unsigned, unsigned> &donja_desna_tacka)
        : gornja_leva_tacka(gornja_leva_tacka), donja_desna_tacka(donja_desna_tacka) {
            std::cout << "ISECANJE :: ISECANJE" << std::endl
                      << "ISECANJE :: ISECANJE :: GORNJA LEVA TACKA :: (" << this->gornja_leva_tacka.first << ", " << this->gornja_leva_tacka.second << ")" << std::endl
                      << "ISECANJE :: ISECANJE :: DONJA DESNA TACKA :: (" << this->donja_desna_tacka.first << ", " << this->donja_desna_tacka.second << ")" << std::endl;
    }

    std::shared_ptr<Slika> isecanje::primeni(std::shared_ptr<Slika> slika) const {
        slika->iseci(gornja_leva_tacka, donja_desna_tacka);

        std::cout << "ISECANJE :: PRIMENI" << std::endl
                  << "ISECANJE :: PRIMENI :: GORNJA LEVA TACKA :: (" << this->gornja_leva_tacka.first << ", " << this->gornja_leva_tacka.second << ")" << std::endl
                  << "ISECANJE :: PRIMENI :: DONJA DESNA TACKA :: (" << this->donja_desna_tacka.first << ", " << this->donja_desna_tacka.second << ")" << std::endl;

        return slika;
    }

    QVariant isecanje::dohvati_stanje() const {
        QVariantMap map;

        map.insert("tip", "isecanje");
        map.insert("gornja_leva_tacka.first", this->gornja_leva_tacka.first);
        map.insert("gornja_leva_tacka.second", this->gornja_leva_tacka.second);
        map.insert("donja_desna_tacka.first", this->donja_desna_tacka.first);
        map.insert("donja_desna_tacka.second", this->donja_desna_tacka.second);

        std::cout << "ISECANJE :: STANJE" << std::endl
                  << "ISECANJE :: STANJE :: GORNJA LEVA TACKA :: (" << map["gornja_leva_tacka.first"].toUInt() << ", " << map["gornja_leva_tacka.second"].toUInt() << ")" << std::endl
                  << "ISECANJE :: STANJE :: DONJA DESNA TACKA :: (" << map["donja_desna_tacka.first"].toUInt() << ", " << map["donja_desna_tacka.second"].toUInt() << ")" << std::endl;

        return map;
    }
}
