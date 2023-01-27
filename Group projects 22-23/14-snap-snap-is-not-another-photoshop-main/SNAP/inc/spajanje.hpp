#pragma once
#include <string>
#include "qvariant.h"
#include "transformacija_drugog_reda.hpp"
#include "enumi.hpp"

namespace snap {
    class spajanje : public transformacija_drugog_reda {
    public:
        spajanje(const bool horizontalno, const bool obrnutim_redosledom, const Poravnanje &poravnanje, const std::string boja_pozadine);
        std::shared_ptr<Slika> primeni(std::shared_ptr<Slika> prva_slika, std::shared_ptr<Slika> druga_slika) const override;

        QVariant dohvati_stanje() const override;

    private:
        bool horizontalno; // da li ce se slike redjati horizontalno ili vertikalno
        bool obrnutim_redosledom;
        Poravnanje poravnanje; // "left" || "center" || "right" (posto vise volim cist ansi c, ja bih ovde stavio karaktere 'l', 'c' i 'r', ali mora da bude fensi, objektno orijentisano)
        std::string boja_pozadine; // "red" || "green" || "blue" (posto vise volim cist ansi c, ja bih ovde stavio karaktere 'r', 'g' i 'b', ali mora da bude fensi, objektno orijentisano) // alternativa za boju pozadine bi bile rgb vrednosti no to prevazilazi okvire ovog projekta

    };
}
