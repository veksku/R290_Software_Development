#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../inc/cuvar_izlaza.hpp"

TEST_CASE("klasa cuvar_izlaza", "[function]") {
	SECTION("provera da li je u izlazu sacuvana slika odgovarajucih dimenzija") {
		auto sl = std::make_shared<snap::Slika>("../resources/resources/heart.ico");
		auto gsl = std::static_pointer_cast<snap::GotovaSlika>(sl);
		snap::cuvar_izlaza ci(gsl);

		auto nsl = std::dynamic_pointer_cast<snap::Slika>(ci.slika);
		
		REQUIRE(nsl->getHeight() == sl->getHeight());
		REQUIRE(nsl->getWidth() == sl->getWidth());
	}

	SECTION("provera da li je vreme nastanka objekta vece od nula") {
		auto sl = std::make_shared<snap::Slika>("../resources/resources/heart.ico");
		auto gsl = std::static_pointer_cast<snap::GotovaSlika>(sl);
		snap::cuvar_izlaza ci(gsl);

		auto vreme = std::chrono::system_clock::to_time_t(ci.vreme);

		REQUIRE(vreme > 0);
	}
}
