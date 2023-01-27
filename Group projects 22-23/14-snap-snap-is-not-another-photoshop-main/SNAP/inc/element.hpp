#pragma once
#include <chrono>
#include <memory>
#include <stdexcept>
#include <iostream>
#include "qvariant.h"
#include "slika.hpp"
#include "tacka.hpp"

namespace snap {
    class element {

    public:
        // TODO: promeni da snap::proizvodjac projektant._postavi_ulaze inicijalizuje ulaze prema snap::element.broj_ulaza i snap::proizvodjac_projektant._uradi_sliku(unsigned id) izmeniti da ne pamti broj ulaza u strukturi std::pair nego da ih dohvata iz snap::element.broj_ulaza
        const unsigned broj_ulaza;
        const std::chrono::time_point<std::chrono::system_clock> vreme;

        element(const unsigned broj_ulaza);

        // Trenutno je tip promenjen sa GotovaSlika na Slika iz razloga zato sto postoji veliki BUG u proizvodjac_projektant kada se pozove metod primeni (iz klase element)
        virtual std::shared_ptr<Slika> primeni() const = 0;
        virtual std::shared_ptr<Slika> primeni(std::shared_ptr<Slika> slika) const = 0;
        virtual std::shared_ptr<Slika> primeni(std::shared_ptr<Slika> prva_slika, std::shared_ptr<Slika> druga_slika) const = 0;

        virtual QVariant dohvati_stanje() const = 0;
    };
}
