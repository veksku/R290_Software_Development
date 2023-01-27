#include "../inc/element.hpp"

namespace snap {
    element::element(const unsigned int broj_ulaza)
        : broj_ulaza(broj_ulaza), vreme(std::chrono::system_clock::now())
    { }

    std::shared_ptr<Slika> element::primeni() const
    {
        throw std::invalid_argument("POZIV :: OVAJ ELEMENT SE PRIMENJUJE BEZ ARGUMENATA\n");

        return nullptr;
    }

    std::shared_ptr<Slika> element::primeni(std::shared_ptr<Slika> slika) const
    {
        throw std::invalid_argument("POZIV :: OVAJ ELEMENT SE PRIMENJUJE SA JEDNIM ARGUMENATOM\n");

        return nullptr;
    }

    std::shared_ptr<Slika> element::primeni(std::shared_ptr<Slika> prva_slika, std::shared_ptr<Slika> druga_slika) const
    {
        throw std::invalid_argument("POZIV :: OVAJ ELEMENT SE PRIMENJUJE SA DVA ARGUMENATA\n");

        return nullptr;
    }
}
