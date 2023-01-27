#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../inc/proizvodjac_projektant.hpp"

TEST_CASE("klasa proizvodjac_projektant", "[function]") {
	SECTION("provera da li dimenzije ucitane slike odgovaraju dimenzijama slike") {
		snap::proizvodjac_projektant pp();

		snap::Slika sl("../resources/resources/heart.ico");
		unsigned id = pp.dodaj_sliku("../resources/resources/heart.ico");

		std::shared_ptr<snap::Slika> dsl = std::static_pointer_cast<snap::Slika>(pp.uradi_sliku(id));

		REQUIRE(dsl->getWidth() == sl.getWidth());
		REQUIRE(dsl->getHeight() == sl.getHeight());
	}

	SECTION("provera da li postavljanje identifikatora elementa na sopstveni ulaz izaziva gresku") {
		snap::proizvodjac_projektant pp();
		pp.dodaj_sliku("../resources/resources/heart.ico");
		unsigned id = pp.dodaj_enhance();

		REQUIRE_THROWS(pp.promeni_ulaz(id, 0, id));
	}

	SECTION("provera da li brisanje elementa sa nepostojecim identifikatorom izaziva gresku") {
		snap::proizvodjac_projektant pp();

		REQUIRE_THROWS(pp.obrisi_element(0));
	}

	SECTION("provera da li prikazivanje izlaza iz elementa viseg koji nema definisan ulaz izaziva gresku") {
		snap::proizvodjac_projektant pp();
		unsigned id = pp.dodaj_enhance();

		REQUIRE_THROWS(pp.uradi_sliku(id));
	}

	SECTION("provera da li kada mehanizam primeni skaliranje dobija sliku trazenih dimenzija") {
		snap::proizvodjac_projektant pp();
		unsigned id = pp.dodaj_sliku("../resources/resources/heart.ico");

		std::pair<unsigned, unsigned> dims = std::make_pair(480u, 480u);
		id = pp.dodaj_skaliranje(false, false, dims, id);

		std::shared_ptr<snap::Slika> dsl = std::static_pointer_cast<snap::Slika>(pp.uradi_sliku(id));

		REQUIRE(dsl->getWidth() == dims.first);
		REQUIRE(dsl->getHeight() == dims.second);
	}
}