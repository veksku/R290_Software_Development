#pragma once
#include <memory>
#include "slika.hpp"
#include "element.hpp"

namespace snap {
    class transformacija : public element {

    public:
        transformacija(const unsigned broj_ulaza);
        std::shared_ptr<Slika> primeni() const;
        // virtual std::shared_ptr<Slika> primeni(std::shared_ptr<Slika> slika) const = 0;
        // virtual std::shared_ptr<Slika> primeni(std::shared_ptr<Slika> prva_slika, std::shared_ptr<Slika> druga_slika) const = 0;
    };

    inline transformacija::transformacija(const unsigned int broj_ulaza)
        : element(broj_ulaza)
    {

    }

    inline std::shared_ptr<Slika> transformacija::primeni() const
    {
        return element::primeni();
    }
}
