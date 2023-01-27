#pragma once
#include <memory>
#include "element.hpp"
#include "qvariant.h"
#include "slika.hpp"

namespace snap {
    class CuvarSlike : public element {
        public:
            CuvarSlike(const std::string &putanja);

            // NAPOMENA: sve klase bi trebalo da imaju konstruktore; kada nema njih to nam pravi veliki problem pri povezivanju klasa !!!

            std::shared_ptr<Slika> primeni() const override;
            std::shared_ptr<Slika> primeni(std::shared_ptr<Slika> slika) const override;
            std::shared_ptr<Slika> primeni(std::shared_ptr<Slika> prva_slika, std::shared_ptr<Slika> druga_slika) const override;

            QVariant dohvati_stanje() const override;

        private:
            const std::string _putanja;
            const std::shared_ptr<Slika> _original;
    };
}
