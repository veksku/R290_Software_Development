#pragma once
#include "qpoint.h"
#include "qvariant.h"
#include "transformacija_prvog_reda.hpp"

namespace snap {
    class skaliranje : public transformacija_prvog_reda {

    public:
        skaliranje(const bool cuva_odnos_ivica, const bool prema_vecoj_ivici, const std::pair<unsigned, unsigned> &dimenzije);
        std::shared_ptr<Slika> primeni(std::shared_ptr<Slika> slika) const override;

        QVariant dohvati_stanje() const override;
        
    private:
        bool cuva_odnos_ivica; // da li skaliranje cuva odnos ivica
        bool prema_vecoj_ivici; // ako cuva da li se skalira prema vecoj ili manjoj ivici
        std::pair<unsigned, unsigned> dimenzije; // sirina, visina
        // ovde nikakav faktor ne treba da se izmislja jer se zadaju sirina i visina nove slike
    };
}
