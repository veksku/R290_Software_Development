#include "../inc/enhance.hpp"

namespace snap {
	enhance::enhance() {
		std::cout << "ENHANCE :: ENHANCE" << std::endl;
	}

	std::shared_ptr<Slika> enhance::primeni(std::shared_ptr<Slika> slika) const {
		slika->enhance();

		std::cout << "ENHANCE :: PRIMENI" << std::endl;

		return slika;
	}

    QVariant enhance::dohvati_stanje() const {
    	std::cout << "ENHANCE :: STANJE" << std::endl;

    	QVariantMap map;

    	map.insert("tip", "enhance");

        return map;
    }
    // Deckard. B26354.
}
