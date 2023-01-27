#include "../inc/slika.hpp"
#include "../inc/enumi.hpp"

namespace snap {
	Slika::Slika(const std::shared_ptr<Slika> slika) {
		this->m_slika = slika->m_slika;
		this->height = slika->height;
		this->width = slika->width;
	}

    Slika::Slika(std::string path) {
		try {
            m_slika.read(path);
	    }
	    catch( Magick::Exception &error_ ) 
	    { 
            std::cerr << "Magick exception caught Magick::read(): " << error_.what() << std::endl;
            exit(EXIT_FAILURE);
	    }
	    height = m_slika.baseRows();
        width = m_slika.baseColumns();
	}

	Magick::Image Slika::dohvati_sliku() {
	    return this->m_slika;
	}

	void Slika::enhance() {
		m_slika.enhance();
		m_slika.equalize();
		m_slika.normalize();
	}

    void Slika::iseci(const std::pair<unsigned, unsigned> &gornja_leva_tacka, const std::pair<unsigned, unsigned> &donja_desna_tacka) {

	    if(gornja_leva_tacka.first >= donja_desna_tacka.first || gornja_leva_tacka.second >= donja_desna_tacka.second)
			throw std::invalid_argument("SLIKA :: ISECI :: PRVA TACKA MORA BITI STROGO GORNJA LEVA :: DRUGA TACKA MORA BITI STROGO DONJA DESNA\n");

        Slika::m_slika.crop(Magick::Geometry(donja_desna_tacka.first - gornja_leva_tacka.first, donja_desna_tacka.second - gornja_leva_tacka.second, gornja_leva_tacka.first, gornja_leva_tacka.second));
		
        height = m_slika.baseRows();
        width = m_slika.baseColumns();
		
	}

	void Slika::skaliraj(const bool cuva_odnos_ivica, const bool prema_vecoj_ivici, const std::pair<unsigned, unsigned> &dimenzije) {
        int new_width, new_height;
		if(cuva_odnos_ivica) {
			if(prema_vecoj_ivici) {
				if(this->width == std::max(this->width, this->height)) {
					new_width = dimenzije.first;
					new_height = (new_width / (double) this->width) * this->height;
				}
				else {
					new_height = dimenzije.second;
					new_width = (new_height / (double) this->height) * this->width;
				}
			}
			else {
				if(this->width == std::min(this->width, this->height)) {
					new_width = dimenzije.first;
					new_height = (new_width / (double) this->width) * this->height;
				}
				else {
					new_height = dimenzije.second;
					new_width = (new_height / (double) this->height) * this->width;
				}
			}
		}
		else {
			new_width = dimenzije.first;
			new_height = dimenzije.second;
        }

		Slika::m_slika.scale(Magick::Geometry(new_width, new_height, 0, 0));
        height = m_slika.baseRows();
        width = m_slika.baseColumns();
	}

    void Slika::zalepi(std::shared_ptr<Slika> druga_slika, const bool horizontalno, const Poravnanje &poravnanje, const std::string boja_pozadine) {
        if(horizontalno) {
			int total_width = Slika::width + druga_slika->width;
            int total_height = Slika::height > druga_slika->height ? Slika::height : druga_slika->height;
            Magick::Image image(std::to_string(total_width) + "x" + std::to_string(total_height), boja_pozadine);
            //poravnanje moze biti gore, dole, centrirano
            if(poravnanje == Poravnanje::UPPER || Slika::height == druga_slika->height){
                image.composite(Slika::m_slika, 0, 0);
                image.composite(druga_slika->m_slika , Slika::width, 0);
            }
            else if(poravnanje == Poravnanje::LOWER){
                if(total_height == Slika::height){
                    image.composite(Slika::m_slika, 0, 0);
                    image.composite(druga_slika->m_slika , Slika::width, total_height-druga_slika->height);
                }
                else{
                    image.composite(Slika::m_slika, 0, total_height-Slika::height);
                    image.composite(druga_slika->m_slika , Slika::width, 0);
                }
            }
            else if(poravnanje == Poravnanje::CENTER){
                if(total_height == Slika::height){
                    image.composite(Slika::m_slika, 0, 0);
                    image.composite(druga_slika->m_slika , Slika::width, total_height/2 - druga_slika->height/2);
                }
                else{
                    image.composite(Slika::m_slika, 0, total_height/2 - Slika::height/2);
                    image.composite(druga_slika->m_slika , Slika::width, 0);
                }
            }
            Slika::m_slika = image;
		}
        else {
			int total_height = Slika::height + druga_slika->height;
            int total_width = Slika::width > druga_slika->width ? Slika::width : druga_slika->width;
            Magick::Image image(std::to_string(total_width) + "x" + std::to_string(total_height), boja_pozadine);
            //poravnanje moze biti levo, desno, centrirano
            if(poravnanje == Poravnanje::LEFT|| Slika::width == druga_slika->width){
                image.composite(Slika::m_slika, 0, 0);
                image.composite(druga_slika->m_slika , 0, Slika::height);
            }
            else if(poravnanje == Poravnanje::RIGHT){
                if(total_width == Slika::width){
                    image.composite(Slika::m_slika, 0, 0);
                    image.composite(druga_slika->m_slika , total_width - druga_slika->width, total_height - druga_slika->height);
                }
                else{
                    image.composite(Slika::m_slika, total_width - Slika::width, 0);
                    image.composite(druga_slika->m_slika , 0, total_height - druga_slika->height);
                }
            }
            else if(poravnanje == Poravnanje::CENTER){
                if(total_width == Slika::width){
                    image.composite(Slika::m_slika, 0, 0);
                    image.composite(druga_slika->m_slika , total_width/2 - druga_slika->width/2, total_height - druga_slika->height);
                }
                else{
                    image.composite(Slika::m_slika, total_width/2 - Slika::width/2, 0);
                    image.composite(druga_slika->m_slika , 0, total_height - druga_slika->height);
                }
            }
			Slika::m_slika = image;	
		}
		height = m_slika.baseRows();
        width = m_slika.baseColumns();
	}

	bool Slika::sacuvajNaDisku(std::string &putanja) {
	    try {
	        Slika::m_slika.write(putanja);
	        return 1;
		}	
        catch(std::exception const& ex) {
            std::cout << "Greska prilikom cuvanja fajla."<< std::endl << ex.what() << std::endl;
			return 0;
		}
	}

	//pretpostavljamo da zelimo da cuvamo u trenutnom direktorijumu
	bool Slika::sacuvajNaDisku() {
		// TODO: ako postoji nesto u this.putanja cuva na toj putanji inace baca gresku (onda interfejs treba da zahteva od korisnika putanju i poziva se ova gore funkcija)

	    return Slika::sacuvajNaDisku(this->putanja);
	}

	Slika::Slika() : m_slika()
	{
	}

	Slika::Slika(int height, int width) : height(height),
	    width(width)
	{}
	
    int Slika::getHeight() { return this->height; }
    int Slika::getWidth() { return this->width; }
}
