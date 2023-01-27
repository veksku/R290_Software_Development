#include "../inc/proizvodjac_projektant.hpp"

namespace snap {
    void proizvodjac_projektant::_postavi_ulaze(const unsigned id, const std::vector<std::optional<unsigned> > &ulazi) {
    	std::cout << "PROIZVODJAC PROJEKTANT :: M POSTAVI ULAZE :: POCETAK" << std::endl
    			  << "PROIZVODJAC PROJEKTANT :: M POSTAVI ULAZE :: ID ELEMENTA :: " << id << std::endl;

        // provera da li je element sam sebi ulaz
        for(const std::optional<unsigned> &ul : ulazi) {
            if(ul.has_value() && ul.value() == id)
                throw std::invalid_argument("PROIZVODJAC PROJEKTANT :: M POSTAVI ULAZE :: ELEMENT NE MOZE DA BUDE SAM SEBI ULAZ\n");
        }

		// provera da li dimenzije ulaza odgovaraju redu ulaza - ulaz konkretnog elementa mora biti fiksne duzine
		if(ulazi.size() != _elementi[id]->broj_ulaza)
            throw std::invalid_argument("PROIZVODJAC PROJEKTANT :: M POSTAVI ULAZE :: NEODGOVARAJUCI BROJ ULAZNIH ELEMENATA\n");

		// postavljamo ulaze za element sa identifikatorom id
        _tabela_ulaza[id] = ulazi;
        _tabela_ulaza[id].shrink_to_fit();
        std::cout << "PROIZVODJAC PROJEKTANT :: M POSTAVI ULAZE :: ULAZI POSTAVLJENI" << std::endl;

        // ukoliko ulaz elementa id sadrzi neki element onda se azurira izlaz tog elementa
		for(const auto &i : ulazi) {
			if (i.has_value()) {
				_tabela_izlaza[i.value()].insert(id);

				std::cout << "PROIZVODJAC PROJEKTANT :: M POSTAVI ULAZE :: ID ULAZA :: " << i.value() << std::endl
						  << "PROIZVODJAC PROJEKTANT :: M POSTAVI ULAZE :: AZURIRANA TABELA IZLAZA ULAZNOG ELEMENTA" << std::endl;
			}
		}

		std::cout << "PROIZVODJAC PROJEKTANT :: M POSTAVI ULAZE :: KRAJ" << std::endl;
	}

	void proizvodjac_projektant::_dodaj_element(const unsigned id) {
		// She's a replicant, isn't she? 
		_elementi[id] = std::make_shared<enhance>();
	}

    void proizvodjac_projektant::_dodaj_element(const unsigned id, const std::string &putanja) {
        // pravi element snap::cuvar_slike sa zadatom putanjom
        _elementi[id] = std::make_shared<CuvarSlike>(putanja);
	}

	void proizvodjac_projektant::_dodaj_element(const unsigned id, const std::pair<unsigned, unsigned> &gornja_leva_tacka, const std::pair<unsigned, unsigned> &donja_desna_tacka){
        // pravi element snap::isecanje sa zadatom gornjom levom i donjom desnom tackom
        _elementi[id] = std::make_shared<isecanje>(gornja_leva_tacka, donja_desna_tacka);
	}

	void proizvodjac_projektant::_dodaj_element(const unsigned id, const bool cuva_odnos_ivica, const bool prema_vecoj_ivici, const std::pair<unsigned, unsigned> &dimenzije) {
        // pravi element snap::skaliranje sa zadatim novim dimenzijama i nacinu na koji ce nove ivice biti tretirane
        _elementi[id] = std::make_shared<skaliranje>(cuva_odnos_ivica, prema_vecoj_ivici, dimenzije);
	}

    void proizvodjac_projektant::_dodaj_element(const unsigned id, const bool horizontalno, const bool obrnutim_redosledom, const Poravnanje poravnanje, const std::string boja_pozadine) {
        // pravi element snap::spajanje sa zadatim redosledom kojim ce slike biti spojene i kako ce slike biti poredjane sa mogucim levim centralnim i desnim poravnanjem manje slike i bojom koja ce popuniti prostor oko manje slike
        _elementi[id] = std::make_shared<spajanje>(horizontalno, obrnutim_redosledom, poravnanje, boja_pozadine);
	}

	void proizvodjac_projektant::_obrisi_element(const unsigned id) {
		// brise snap::element sa zadatim identifikatorom
		_elementi.erase(id);
	}

	void proizvodjac_projektant::_obrisi_ulaze_izlaze(const unsigned id) {
		std::cout << "PROIZVODJAC PROJEKTANT :: M OBRISI ULAZE IZLAZE :: POCETAK" << std::endl
				  << "PROIZVODJAC PROJEKTANT :: M OBRISI ULAZE IZLAZE :: ID ELEMENTA :: " << id << std::endl;

		// brise identifikator id elementa iz tabele izlaza onih koji su mu bili ulaz
		for(const std::optional<unsigned> &i : _tabela_ulaza[id]) {
			if(i.has_value()) {
				_tabela_izlaza[i.value()].erase(id);

				std::cout << "PROIZVODJAC PROJEKTANT :: M OBRISI ULAZE IZLAZE :: OBRISAN SA IZLAZA ELEMENTA :: " << i.value() << std::endl;
			}
		}

		// brise identifikator elementa iz tabele ulaza onih kojima je bio ulaz
		for(unsigned i : _tabela_izlaza[id]) {
			auto it = std::find(_tabela_ulaza[i].begin(), _tabela_ulaza[i].end(), id);
			if(it != _tabela_ulaza[i].end())
	            it->reset();

	        std::cout << "PROIZVODJAC PROJEKTANT :: M OBRISI ULAZE IZLAZE :: OBRISAN SA ULAZA ELEMENTA :: " << i << std::endl;
		}

		// brisem ga iz tabele izlaza
		_tabela_izlaza.erase(id);
		std::cout << "PROIZVODJAC PROJEKTANT :: M OBRISI ULAZE IZLAZE :: OBRISANA TABELA IZLAZA ELEMENTA :: " << id << std::endl;

		// brisem ga iz tabele ulaza
		_tabela_ulaza.erase(id);
		std::cout << "PROIZVODJAC PROJEKTANT :: M OBRISI ULAZE IZLAZE :: OBRISANA TABELA ULAZA ELEMENTA :: " << id << std::endl;

		std::cout << "PROIZVODJAC PROJEKTANT :: M OBRISI ULAZE IZLAZE :: KRAJ" << std::endl;
	}

	// SUPERHACK :: ova funkcija moze da se podeli na vise manjih funkcija
    std::shared_ptr<GotovaSlika> proizvodjac_projektant::_uradi_sliku(const unsigned id) {
    	std::cout << "PROIZVODJAC PROJEKTANT :: M URADI SLIKU :: POCETAK" << std::endl;

		// trazi se slika na izlazu lanca elementa sa identifikatorom id
		std::stack<unsigned> ulaz_stack;
        std::stack<std::shared_ptr<element> > element_stack; // ovde smo mogli da cuvamo i id-jeve
		
		// prvo stavljamo id elementa ciji izlaz trazimo na stek ulaznih id-jeva
		ulaz_stack.push(id);
		// i element sa datim identifikatorom dodajemo na stek elemenaa
		element_stack.push(_elementi[id]);
        
		// imamo prolazak kroz lanac elemenata u grafu gde pravimo stek od ulaznih elemenata elementa id i ulaznih elemenata njegovih ulaznih elemenata
		while(!ulaz_stack.empty()) {
			// prvo uzimamo id elementa cije ulaze trazimo i skidamo taj element sa steka
			unsigned _id = ulaz_stack.top();
			ulaz_stack.pop();

			std:: cout << "PROIZVODJAC PROJEKTANT :: M URADI SLIKU :: ID ELEMENTA :: " << _id << std::endl;

			// dodajemo sve ulazne elemente trenutnog elementa u stek elemenata
			const std::vector<std::optional<unsigned> > &_ulazi = _tabela_ulaza[_id];
            for(const std::optional<unsigned> &x : _ulazi) {

				if(!x.has_value())
					throw std::invalid_argument("PROIZVODJAC PROJEKTANT :: M URADI SLIKU :: ELEMENT BEZ DEFINISANOG ODGOVARAJUCEG ULAZA\n");
				ulaz_stack.push(x.value());
                element_stack.push(_elementi[x.value()]);

                std::cout << "PROIZVODJAC PROJEKTANT :: M URADI SLIKU :: ID ULAZA :: " << x.value() << std::endl;
			}
        }

        // obradjene slike cemo stavljati na stek slika
        std::stack<std::shared_ptr<Slika> > slika_stack;

        // kada napravimo stek svih elemata koje treba primeniti skidamo jedan po jedan element sa steka i primenjujemo ga
		while(!element_stack.empty()) {
			std::cout << "PROIZVODJAC PROJEKTANT :: M URADI SLIKU :: PRIMENA SLEDECEG ELEMENATA" << std::endl;

			// uzimamo element sa steka koji bi trebalo da primenimo
            std::shared_ptr<element> x = element_stack.top();
			element_stack.pop();
			
			// HACK :: switch je najbolja stvar na svetu i haters gonna hate
			// u skladu sa brojem slika koji element zahteva na ulazu skidamo elemente sa steka sa slikama i prosledjujemo ih elementu i rezultujucu sliku vracamo na stek sa slikama
			switch(x->broj_ulaza) {
			case 0: {
				slika_stack.push(x->primeni());
				break;
			}
            case 1: {
                std::shared_ptr<Slika> a = slika_stack.top();
                slika_stack.pop();
                slika_stack.push(x->primeni(a));
                break;
            }
            case 2: {
	            std::shared_ptr<Slika> a = slika_stack.top();
				slika_stack.pop();
				std::shared_ptr<Slika> b = slika_stack.top();
				slika_stack.pop();
	            slika_stack.push(x->primeni(a, b));
				break;
            }
			default:
                throw std::invalid_argument("PROIZVODJAC PROJEKTANT :: M URADI SLIKU ::  NE POSTOJI ELEMENT SA VISE OD 2 ULAZA\n");
			}
		}

		std::cout << "PROIZVODJAC PROJEKTANT :: M URADI SLIKU :: KRAJ" << std::endl;

		// poslednja slika koja ostane na steku sa slikama je slika koju trazimo
        return std::static_pointer_cast<GotovaSlika>(slika_stack.top());
    }

	std::chrono::time_point<std::chrono::system_clock> proizvodjac_projektant::_vreme_izmene(const unsigned id) const {
		std::cout << "PROIZVODJAC PROJEKTANT :: M VREME IZMENE" << std::endl
				  << "PROIZVODJAC PROJEKTANT :: M VREME IZMENE :: ID ELEMENTA :: " << id << std::endl;

		// pronalazi vreme poslednje izmene u lancu elemenata koji se zavrsava sa elementom koji ima identifikator id
		const std::shared_ptr<element> _element = _elementi.at(id);
		std::chrono::time_point<std::chrono::system_clock> vreme = _element->vreme;

		// prolazak kroz lanac elemenata u grafu gde trazimo posledlje vreme izmene elementa u lancu
		std::stack<unsigned> ulazni_elementi;
		ulazni_elementi.push(id);
		while(!ulazni_elementi.empty()) {
			unsigned _id = ulazni_elementi.top();
            ulazni_elementi.pop();
			const std::vector<std::optional<unsigned> > &_ulazi = _tabela_ulaza.at(_id); 
			//ukoliko se naidje na out of range gresku, zameniti  ^^^^^^^^^^^^^^^^^^^^^  sa _tabela_ulaza[_id] // ako se naidje na out of range gresku znaci da se pristupa elementu koji ne postoji u mapi
			for(const std::optional<unsigned> &x : _ulazi) {
				if(!x.has_value())
					throw std::invalid_argument("PROIZVODJAC PROJEKTANT :: M VREME IZMENE :: ELEMENT BEZ DEFINISANOG ODGOVARAJUCEG ULAZA\n");
				ulazni_elementi.push(x.value());
				const std::shared_ptr<element> _element = _elementi.at(x.value());
				vreme = std::max(vreme, _element->vreme);
			}
		}

		return vreme;
	}

	proizvodjac_projektant::proizvodjac_projektant() {
		static unsigned brojac_instanci{ 0 };

		if(++brojac_instanci > 1)
			throw std::logic_error("PROIZVODJAC PROJEKTANT :: PROIZVODJAC PROJEKTANT :: NE MOZE POSTOJATI VISE OD JEDNE INSTANCE\n");

		std::cout << "PROIZVODJAC PROJEKTANT :: PROIZVODJAC PROJEKTANT" << std::endl;
	}
	
	unsigned proizvodjac_projektant::dodaj_sliku(const std::string &putanja) {
    	std::cout << "PROIZVODJAC PROJEKTANT :: DODAJ SLIKU" << std::endl;

    	// dodajem novu sliku
        this->_dodaj_element(_id_novog_elementa, putanja);

		return _id_novog_elementa++;
	}

//<<<<<<< HEAD
//	unsigned proizvodjac_projektant::dodaj_element(const std::optional<unsigned> id_ulaza) {
//=======
    unsigned proizvodjac_projektant::dodaj_enhance(const std::optional<unsigned> id_ulaza) {
//>>>>>>> 0daaa3dbb8373a20b1d23d8d716a18620f7529cc
    	std::cout << "PROIZVODJAC PROJEKTANT :: DODAJ ENHANCE" << std::endl;

		// dodajem novu enhance transformaciju
        this->_dodaj_element(_id_novog_elementa);
		this->_postavi_ulaze(_id_novog_elementa, { id_ulaza });

		return _id_novog_elementa++;
	}

	unsigned proizvodjac_projektant::dodaj_isecanje(const std::pair<unsigned, unsigned> &gornja_leva_tacka, const std::pair<unsigned, unsigned> &donja_desna_tacka, const std::optional<unsigned> id_ulaza) {
		std::cout << "PROIZVODJAC PROJEKTANT :: DODAJ ISECANJE" << std::endl;

		// dodajem novo isecanje
        this->_dodaj_element(_id_novog_elementa, gornja_leva_tacka, donja_desna_tacka);
        this->_postavi_ulaze(_id_novog_elementa, { id_ulaza });

		return _id_novog_elementa++;
	}

	unsigned proizvodjac_projektant::dodaj_skaliranje(const bool cuva_odnos_ivica, const bool prema_vecoj_ivici, const std::pair<unsigned, unsigned> &dimenzije, const std::optional<unsigned> id_ulaza) {
		std::cout << "PROIZVODJAC PROJEKTANT :: DODAJ SKALIRANJE" << std::endl;

		// dodajem novo skaliranje
        this->_dodaj_element(_id_novog_elementa, cuva_odnos_ivica, prema_vecoj_ivici, dimenzije);
        this->_postavi_ulaze(_id_novog_elementa, { id_ulaza });

        return _id_novog_elementa++;
	}

    unsigned proizvodjac_projektant::dodaj_spajanje(const bool horizontalno, const bool obrnutim_redosledom, const Poravnanje poravnanje, const std::string boja_pozadine, const std::optional<unsigned> id_prvog_ulaza, const std::optional<unsigned> id_drugog_ulaza) {
    	std::cout << "PROIZVODJAC PROJEKTANT :: DODAJ SPAJANJE" << std::endl;

		// dodajem novo spajanje
        this->_dodaj_element(_id_novog_elementa, horizontalno, obrnutim_redosledom, poravnanje, boja_pozadine);
        this->_postavi_ulaze(_id_novog_elementa, { id_prvog_ulaza, id_drugog_ulaza });

		return _id_novog_elementa++;
	}

	// TODO: mogu li nekako da promenim _postavi_ulaz da moze da se iskoristi i za inicijalizaciju ulaza i za promenu ulaza?
	void proizvodjac_projektant::promeni_ulaz(const unsigned id, const unsigned pozicija_ulaza, const unsigned id_novog_ulaza) {
		std::cout << "PROIZVODJAC PROJEKTANT :: PROMENI ULAZ" << std::endl
				  << "PROIZVODJAC PROJEKTANT :: PROMENI ULAZ :: ID ELEMENTA :: " << id << std::endl
				  << "PROIZVODJAC PROJEKTANT :: PROMENI ULAZ :: POZICIJA ULAZA :: " << pozicija_ulaza << std::endl
				  << "PROIZVODJAC PROJEKTANT :: PROMENI ULAZ :: ID NOVOG ULAZA :: " << id_novog_ulaza << std::endl;

		if(id == id_novog_ulaza)
			throw std::invalid_argument("PROIZVODJAC PROJEKTANT :: PROMENI ULAZ :: ELEMENT NE MOZE DA BUDE SAM SEBI ULAZ\n");

		if(_elementi.at(id)->broj_ulaza <= pozicija_ulaza)
            throw std::invalid_argument("PROIZVODJAC PROJEKTANT :: PROMENI ULAZ :: PREKORACENJE DIMENZIJE ULAZA\n");

		if(_tabela_ulaza.at(id)[pozicija_ulaza].has_value()) {
			unsigned id_ulaznog_el = _tabela_ulaza.at(id)[pozicija_ulaza].value();
			_tabela_izlaza.at(id_ulaznog_el).erase(id);
		}

		_tabela_ulaza[id][pozicija_ulaza] = id_novog_ulaza;
		_tabela_izlaza[id_novog_ulaza].insert(id);
	}
   
	void proizvodjac_projektant::promeni_sliku(const unsigned id, const std::string &putanja) {
        std::cout << "PROIZVODJAC PROJEKTANT :: PROMENI SLIKU" << std::endl;

        if(_elementi.find(id) != _elementi.end()){
	        // brise staru i dodaje novu sliku na istoj poziciji u grafu
	        this->_obrisi_element(id);
	        this->_dodaj_element(id, putanja);
        }
        else
			throw std::invalid_argument("PROIZVODJAC PROJEKTANT :: PROMENI SLIKU :: NE POSTOJI ELEMENT SA DATIM ID\n");
	}

	void proizvodjac_projektant::promeni_isecanje(const unsigned id, const std::pair<unsigned, unsigned> &gornja_leva_tacka, const std::pair<unsigned, unsigned> &donja_desna_tacka) {
        std::cout << "PROIZVODJAC PROJEKTANT :: PROMENI ISECANJE" << std::endl;

        if(_elementi.find(id) != _elementi.end()){
	        // brise staro i dodaje novo isecanje na istoj poziciji u grafu
	        this->_obrisi_element(id);
	        this->_dodaj_element(id, gornja_leva_tacka, donja_desna_tacka);
	    }
        else
			throw std::invalid_argument("PROIZVODJAC PROJEKTANT :: PROMENI ISECANJE :: NE POSTOJI ELEMENT SA DATIM ID\n");
	}
	
	void proizvodjac_projektant::promeni_skaliranje(const unsigned id, const bool cuva_odnos_ivica, const bool prema_vecoj_ivici, const std::pair<unsigned, unsigned> &dimenzije) {
		std::cout << "PROIZVODJAC PROJEKTANT :: PROMENI SKALIRANJE" << std::endl;

		if(_elementi.find(id) != _elementi.end()){
	        // brise staro i dodaje novo skaliranje u istoj poziciji u grafu
	        this->_obrisi_element(id);
	        this->_dodaj_element(id, cuva_odnos_ivica, prema_vecoj_ivici, dimenzije);
    	}
	    else
			throw std::invalid_argument("PROIZVODJAC PROJEKTANT :: PROMENI SKALIRANJE :: NE POSTOJI ELEMENT SA DATIM ID\n");
	}
	
    void proizvodjac_projektant::promeni_spajanje(const unsigned id, const bool horizontalno, const bool obrnutim_redosledom, const Poravnanje poravnanje, const std::string boja_pozadine) {
        std::cout << "PROIZVODJAC PROJEKTANT :: PROMENI SPAJANJE" << std::endl;

        if(_elementi.find(id) != _elementi.end()){
	        // brise staro i dodaje novo spajanje na istoj poziciji u grafu
	        this->_obrisi_element(id);
	        this->_dodaj_element(id, horizontalno, obrnutim_redosledom, poravnanje, boja_pozadine);
	    }
        else
			throw std::invalid_argument("PROIZVODJAC PROJEKTANT :: PROMENI SPAJANJE :: NE POSTOJI ELEMENT SA DATIM ID\n");
	}

	void proizvodjac_projektant::obrisi_element(const unsigned id) {
		std::cout << "PROIZVODJAC PROJEKTANT :: OBRISI ELEMENT" << std::endl;

		if(_elementi.find(id) != _elementi.end()){
			// brise sve informacije o elementu sa identifikatorom id
	        this->_obrisi_ulaze_izlaze(id);
	        this->_obrisi_element(id);
		}
		else
			throw std::invalid_argument("PROIZVODJAC PROJEKTANT :: OBRISI ELEMENT :: NE POSTOJI ELEMENT SA DATIM ID\n");
    }

    // Magick::Image proizvodjac_projektant::vratiTrenutnuSliku()
    // {
    //     return tmpSlika.dohvati_sliku();
    //     //return uradi_sliku(id)->dohvati_sliku();
    // }


    std::shared_ptr<GotovaSlika> proizvodjac_projektant::uradi_sliku(const unsigned id) {
        /*if(!_gotove_slike.contains(id) || _gotove_slike[id].vreme_poslednje_izmene < this->_vreme_izmene(id)) {
            _gotove_slike[id] = std::make_unique<cuvar_gotovih_slika>(this->_uradi_sliku(id));
			return _gotove_slike[id].dohvati_sliku();
		}
		else
            return _gotove_slike[id].dohvati_sliku();*/
    	std::cout << "PROIZVODJAC PROJEKTANT :: URADI SLIKU" << std::endl;

        if(_gotove_slike.find(id) == _gotove_slike.end() || _gotove_slike.at(id)->vreme < this->_vreme_izmene(id)) {

            _gotove_slike[id] = std::make_shared<cuvar_izlaza>(this->_uradi_sliku(id));
            return _gotove_slike.at(id)->slika;
        }
        else {
            std::cout << "Gotova slika" << std::endl;
            return _gotove_slike.at(id)->slika;
        }
    }

    QVariant proizvodjac_projektant::dohvati_stanje() const {
		std::cout << "PROIZVODJAC PROJEKTANT :: DOHVATI STANJE :: POCETAK" << std::endl;

        QVariantList lista;

        for(const auto &[id, element] : _elementi) {
            std::cout << "PROIZVODJAC PROJEKTANT :: DOHVATI STANJE :: ELEMENT ID :: " << id << std::endl;

            QVariantMap mapa = element->dohvati_stanje().toMap();

            mapa.insert("id", id);

            switch(element->broj_ulaza) {
            case 0:
                break;
            case 1:
                if(_tabela_ulaza.at(id)[0].has_value())
                    mapa.insert("ulaz", _tabela_ulaza.at(id)[0].value());
                else
                    mapa.insert("ulaz", QVariant::fromValue(nullptr));
                std::cout << "PROIZVODJAC PROJEKTANT :: DOHVATI STANJE :: ID ULAZA :: " << mapa["ulaz"].toString().toStdString() << std::endl;
                break;
            case 2:
                if(_tabela_ulaza.at(id)[0].has_value())
                    mapa.insert("ulaz1", _tabela_ulaza.at(id)[0].value());
                else
                    mapa.insert("ulaz1", QVariant::fromValue(nullptr));

                if(_tabela_ulaza.at(id)[1].has_value())
                    mapa.insert("ulaz2", _tabela_ulaza.at(id)[1].value());
                else
                    mapa.insert("ulaz2", QVariant::fromValue(nullptr));

                std::cout << "PROIZVODJAC PROJEKTANT :: DOHVATI STANJE :: ID 1. ULAZA :: " << mapa["ulaz1"].toString().toStdString() << std::endl
                		  << "PROIZVODJAC PROJEKTANT :: DOHVATI STANJE :: ID 2. ULAZA :: " << mapa["ulaz2"].toString().toStdString() << std::endl;
                break;
            default:
                throw std::invalid_argument("PROIZVODJAC PROJEKTANT :: DOHVATI STANJE :: NEDOZVOLJENA VREDNOST BROJA ULAZA\n");
            }

            lista.append(mapa);
        }

        std::cout << "PROIZVODJAC PROJEKTANT :: DOHVATI STANJE :: KRAJ" << std::endl;

        return lista;
    }

    void proizvodjac_projektant::postavi_stanje(const QVariant &stanje) {
    	std::cout << "PROIZVODJAC PROJEKTANT :: POSTAVI STANJE :: POCETAK" << std::endl;

        const QVariantList &lista = stanje.toList();

        for(const QVariant &var : lista) {
            const QVariantMap &mapa = var.toMap();

            unsigned id = mapa["id"].toUInt();

            std::cout << "PROIZVODJAC PROJEKTANT :: POSTAVI STANJE :: ELEMENT ID :: " << id << std::endl;

            if(mapa["tip"] == "enhance") {
                this->_dodaj_element(id);

                if(mapa["ulaz"].isNull())
                    this->_postavi_ulaze(id, { std::nullopt });
                else
                    this->_postavi_ulaze(id, { mapa["ulaz"].toUInt() });
            }
            else if(mapa["tip"] == "isecanje") {
                const std::pair<unsigned, unsigned> gornja_leva_tacka = std::make_pair(mapa["gornja_leva_tacka.first"].toUInt(), mapa["gornja_leva_tacka.second"].toUInt());
                const std::pair<unsigned, unsigned> donja_desna_tacka = std::make_pair(mapa["donja_desna_tacka.first"].toUInt(), mapa["donja_desna_tacka.second"].toUInt());

                this->_dodaj_element(id, gornja_leva_tacka, donja_desna_tacka);

                if(mapa["ulaz"].isNull())
                    this->_postavi_ulaze(id, { std::nullopt });
                else
                    this->_postavi_ulaze(id, { mapa["ulaz"].toUInt() });
            }
            else if(mapa["tip"] == "skaliranje") {
                const bool cuva_odnos_ivica = mapa["cuva_odnos_ivica"].toBool();
                const bool prema_vecoj_ivici = mapa["prema_vecoj_ivici"].toBool();
                const std::pair<unsigned, unsigned> dimenzije = std::make_pair(mapa["dimenzije.first"].toUInt(), mapa["dimenzije.second"].toUInt());

                this->_dodaj_element(id, cuva_odnos_ivica, prema_vecoj_ivici, dimenzije);

                if(mapa["ulaz"].isNull())
                    this->_postavi_ulaze(id, { std::nullopt });
                else
                    this->_postavi_ulaze(id, { mapa["ulaz"].toUInt() });
            }
            else if(mapa["tip"] == "spajanje") {
                std::vector<std::optional<unsigned> > uzlazi = {};

                const bool horizontalno = mapa["horizontalno"].toBool();
                const bool obrnutim_redosledom = mapa["obrnutim_redosledom"].toBool();
                const std::string poravnanje = mapa["poravnanje"].toString().toStdString();
                const std::string boja_pozadine = mapa["boja_pozadine"].toString().toStdString();

                Poravnanje por = poravnanje_from_string(poravnanje);

                this->_dodaj_element(id, horizontalno, obrnutim_redosledom, por, boja_pozadine);

                if(mapa["ulaz1"].isNull())
                    uzlazi.push_back(std::nullopt);
                else
                    uzlazi.push_back(mapa["ulaz1"].toUInt());
                if(mapa["ulaz2"].isNull())
                    uzlazi.push_back(std::nullopt);
                else
                    uzlazi.push_back(mapa["ulaz2"].toUInt());

                this->_postavi_ulaze(id, uzlazi);
            }
            else if(mapa["tip"] == "cuvar_slike") {
                const std::string putanja = mapa["putanja"].toString().toStdString();

                this->_dodaj_element(id, putanja);
            }
            else
                throw std::invalid_argument("PROIZVODJAC PROJEKTANT :: POSTAVI STANJE :: NEPOSTOJECI TIP ELEMENTA\n");

            _id_novog_elementa = std::max(++id, _id_novog_elementa);

            std::cout << "PROIZVODJAC PROJEKTANT :: POSTAVI STANJE :: KRAJ" << std::endl;
        }
    }

    void proizvodjac_projektant::reset() {
    	std::cout << "PROIZVODJAC PROJEKTANT :: RESET" << std::endl;

    	this->_elementi.clear();
    	this->_gotove_slike.clear();
    	this->_tabela_izlaza.clear();
    	this->_tabela_ulaza.clear();
    	this->_id_novog_elementa = 0;
    }

    // void proizvodjac_projektant::dodajTmpSliku(const std::string &putanja)
    // {
    //     tmpSlika = Slika(putanja);
    //     dodaj_element(putanja);
    // }

}

// obraditi izuzetke
