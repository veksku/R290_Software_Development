#include "qvariant.h"
#include "transformacija_prvog_reda.hpp"

namespace snap {
	class enhance : public transformacija_prvog_reda {
	public:
		enhance();
		std::shared_ptr<Slika> primeni(std::shared_ptr<Slika> slika) const override;

        QVariant dohvati_stanje() const override;
    };
	// We call it Voight-Kampff for short.
}
