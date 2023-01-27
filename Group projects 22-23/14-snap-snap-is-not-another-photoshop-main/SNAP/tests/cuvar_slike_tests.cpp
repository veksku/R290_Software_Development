#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <memory>

#include "../inc/CuvarSlike.hpp"

TEST_CASE("klasa CuvarSlike", "[function]") {
	SECTION("primeni bez parametara") {
		snap::Slika sl("../resources/resources/heart.ico");
		snap::CuvarSlike cs("../resources/resources/heart.ico");

		REQUIRE_NOTHROW(cs.primeni());
		REQUIRE(cs.primeni()->getHeight() == sl.getHeight());
		REQUIRE(cs.primeni()->getWidth() == sl.getWidth());
	}

	SECTION("primeni sa jednim parametrom") {
		std::shared_ptr<snap::Slika> sl;

		snap::CuvarSlike cs("../resources/resources/heart.ico");

		REQUIRE_THROWS(cs.primeni(sl));
	}

	SECTION("primeni sa dva parametra") {
		std::shared_ptr<snap::Slika> sl1 = std::make_shared("../resources/resources/heart.ico");
		std::shared_ptr<snap::Slika> sl2 = std::make_shared("../resources/resources/heart.ico");

		snap::CuvarSlike cs("../resources/resources/heart.ico");

		REQUIRE_THROWS(cs.primeni(sl1, sl2));
	}
}
