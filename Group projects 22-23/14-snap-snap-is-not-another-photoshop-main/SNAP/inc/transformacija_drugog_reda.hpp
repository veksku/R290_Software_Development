#pragma once
#include "slika.hpp"
#include "transformacija.hpp"

namespace snap {
    class transformacija_drugog_reda : public transformacija {
        
    public:
        transformacija_drugog_reda();
        std::shared_ptr<Slika> primeni(std::shared_ptr<Slika> slika) const override;
        // virtual std::shared_ptr<Slika> primeni(std::shared_ptr<Slika> prva_slika, std::shared_ptr<Slika> druga_slika) const = 0;
    };
}
