#pragma once
#include <memory>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include "GotovaSlika.hpp"
#include "enumi.hpp"

namespace snap {
    class Slika : public GotovaSlika {

    public:
        Slika(const std::shared_ptr<Slika> slika);
        Slika(std::string path);
        Slika(int height, int width);
        Slika();
        void enhance();
    	void iseci(const std::pair<unsigned, unsigned> &gornja_leva_tacka, const std::pair<unsigned, unsigned> &donja_desna_tacka);
        // void iseci(Tacka A, Tacka B);
    	//void skaliraj(bool cuva_odnos_ivica, bool prema_vecoj_ivici, std::tuple<unsigned,unsigned> dimenzije); 
        //kompleksnija implementacija, pogledati na kraju projekta ako bude bilo vremena
    	void skaliraj(const bool cuva_odnos_ivica, const bool prema_vecoj_ivici, const std::pair<unsigned, unsigned> &dimenzije);
        void zalepi(std::shared_ptr<Slika> druga_slika, const bool horizontalno, const Poravnanje &poravnanje, const std::string boja_pozadine); // poravnanje: "left" || "center" || "right", boja_pozadine: "red" || "green" || "blue" // alternativa za boju pozadine bi bile rgb vrednosti no to prevazilazi okvire ovog projekta
        //std::tuple<unsigned, unsigned> dohvati_dimenzije(); //nepotrebno? za sada se dimenzije traze samo u metodama klase Slika
        bool sacuvajNaDisku(std::string &putanja) override;
        bool sacuvajNaDisku() override;
        Magick::Image dohvati_sliku() override;
        Magick::Image m_slika; // TODO: da li ovo zaista treba da bude javno?
    	int getHeight();
    	int getWidth();
    private:
    	int height=0, width=0;
        std::string putanja;
    };
}
