#include "../inc/transformacija_prvog_reda.hpp"

namespace snap {
	transformacija_prvog_reda::transformacija_prvog_reda()
        : transformacija(1u)
	{}

	std::shared_ptr<Slika> transformacija_prvog_reda::primeni(std::shared_ptr<Slika> prva_slika, std::shared_ptr<Slika> druga_slika) const {
		return element::primeni(prva_slika, druga_slika);
	}
}
