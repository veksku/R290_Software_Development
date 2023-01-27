#pragma once
#include "slika.hpp"
#include "transformacija.hpp"

namespace snap {
    class transformacija_prvog_reda : public transformacija {

    public:
        transformacija_prvog_reda();
        // virtual std::shared_ptr<Slika> primeni(std::shared_ptr<Slika> slika) const = 0;
        std::shared_ptr<Slika> primeni(std::shared_ptr<Slika> prva_slika, std::shared_ptr<Slika> druga_slika) const override;
    };
}