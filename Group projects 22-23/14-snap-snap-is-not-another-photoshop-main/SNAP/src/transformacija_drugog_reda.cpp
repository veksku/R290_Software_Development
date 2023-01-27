#include "../inc/transformacija_drugog_reda.hpp"

namespace snap {
	transformacija_drugog_reda::transformacija_drugog_reda()
        : transformacija(2u)
	{}
	
    std::shared_ptr<Slika> transformacija_drugog_reda::primeni(std::shared_ptr<Slika> slika) const {
    	return element::primeni(slika);
    }
}
