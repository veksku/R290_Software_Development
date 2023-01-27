#pragma once

#include <map>
#include <set>
#include <stack>
#include <vector>
#include <string>
#include <chrono>
#include <optional>
#include <utility>
#include <memory>
#include <algorithm>
#include <stdexcept>
#include "element.hpp"
#include "slika.hpp"
#include "GotovaSlika.hpp"
#include "cuvar_izlaza.hpp"
#include "isecanje.hpp"
#include "enhance.hpp"
#include "spajanje.hpp"
#include "skaliranje.hpp"
#include "CuvarSlike.hpp"

namespace snap {
	class proizvodjac_projektant
	{
		std::map<unsigned, std::shared_ptr<element> > _elementi;
        std::map<unsigned, std::shared_ptr<cuvar_izlaza> > _gotove_slike;
		std::map<unsigned, std::set<unsigned> > _tabela_izlaza;
		std::map<unsigned, std::vector<std::optional<unsigned> > > _tabela_ulaza;
		
		unsigned _id_novog_elementa = 0;

		void _postavi_ulaze(const unsigned id, const std::vector<std::optional<unsigned> > &ulazi);
		void _dodaj_element(const unsigned id);
		void _dodaj_element(const unsigned id, const std::string &putanja);
		void _dodaj_element(const unsigned id, const std::pair<unsigned, unsigned> &gornja_leva_tacka, const std::pair<unsigned, unsigned> &donja_desna_tacka);
		void _dodaj_element(const unsigned id, const bool cuva_odnos_ivica, const bool prema_vecoj_ivici, const std::pair<unsigned, unsigned> &dimenzije);
        void _dodaj_element(const unsigned id, const bool horizontalno, const bool obrnutim_redosledom, const Poravnanje poravnanje, const std::string boja_pozadine);
		void _obrisi_element(const unsigned id);
		void _obrisi_ulaze_izlaze(const unsigned id);
        std::shared_ptr<GotovaSlika> _uradi_sliku(const unsigned id);
		std::chrono::time_point<std::chrono::system_clock> _vreme_izmene(const unsigned id) const;

	public:
        proizvodjac_projektant();
		
		unsigned dodaj_sliku(const std::string &putanja); // dodaj sliku
		unsigned dodaj_enhance(const std::optional<unsigned> id_ulaza = std::nullopt); // dodaj enhance
		unsigned dodaj_isecanje(const std::pair<unsigned, unsigned> &gornja_leva_tacka, const std::pair<unsigned, unsigned> &donja_desna_tacka, const std::optional<unsigned> id_ulaza = std::nullopt); // dodaj isecanje
		unsigned dodaj_skaliranje(const bool cuva_odnos_ivica, const bool prema_vecoj_ivici, const std::pair<unsigned, unsigned> &dimenzije, const std::optional<unsigned> id_ulaza = std::nullopt); // dodaj skaliranje
        unsigned dodaj_spajanje(const bool horizontalno, const bool obrnutim_redosledom, const Poravnanje poravnanje, const std::string boja_pozadine, const std::optional<unsigned> id_prvog_ulaza = std::nullopt, const std::optional<unsigned> id_drugog_ulaza = std::nullopt); // dodaj spajanje
		
		void promeni_ulaz(const unsigned id, const unsigned pozicija_ulaza, const unsigned id_novog_ulaza);
		
		void promeni_sliku(const unsigned id, const std::string &putanja); // zameni sliku
		void promeni_isecanje(const unsigned id, const std::pair<unsigned, unsigned> &gornja_leva_tacka, const std::pair<unsigned, unsigned> &donja_desna_tacka); // promeni_isecanje
		void promeni_skaliranje(const unsigned id, const bool cuva_odnos_ivica, const bool prema_vecoj_ivici, const std::pair<unsigned, unsigned> &dimenzije); // promeni skaliranje
        void promeni_spajanje(const unsigned id, const bool horizontalno, const bool obrnutim_redosledom, const Poravnanje poravnanje, const std::string boja_pozadine); // promeni spajanje
		void obrisi_element(const unsigned id);
        std::shared_ptr<GotovaSlika> uradi_sliku(const unsigned id);

        QVariant dohvati_stanje() const;
        void postavi_stanje(const QVariant &stanje);

        void reset();

        // privremena pomocna funkcija
        Slika tmpSlika;
        void dodajTmpSliku(const std::string &putanja);
        Magick::Image vratiTrenutnuSliku();
	};
}
