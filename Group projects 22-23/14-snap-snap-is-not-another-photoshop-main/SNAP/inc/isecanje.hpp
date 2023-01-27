#pragma once
#include <memory>
#include "qpoint.h"
#include "qvariant.h"
#include "transformacija_prvog_reda.hpp"

namespace snap {
    class isecanje : public transformacija_prvog_reda {

    public:
        isecanje(const std::pair<unsigned, unsigned> &gornja_leva_tacka, const std::pair<unsigned, unsigned> &donja_desna_tacka);

        std::shared_ptr<Slika> primeni(std::shared_ptr<Slika> slika) const override;

        QVariant dohvati_stanje() const override;
        
    private:
        const std::pair<unsigned, unsigned> gornja_leva_tacka;
        const std::pair<unsigned, unsigned> donja_desna_tacka;

    };
}
