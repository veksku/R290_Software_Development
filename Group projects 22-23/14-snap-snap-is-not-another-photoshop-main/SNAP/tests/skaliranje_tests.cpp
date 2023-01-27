#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <cstdlib>

#include "../inc/skaliranje.hpp"
#include "../inc/slika.hpp"


TEST_CASE("klasa skaliranje", "[function]")
{
    

SECTION("Skaliranje slike")
    {
        //arrange
        snap::Slika s("../resources/resources/heart.ico");
        const auto skaliranje_height = rand() % s.getHeight();
        const auto skaliranje_width = rand() % s.getWidth();
        const auto current_width = s.getWidth();
        const auto current_height = s.getHeight();
                
        const bool cuva_odnos_ivica = false;
        const bool prema_vecoj_ivici = (rand() % 2 == 0 ? true : false);
        
        snap::skaliranje sk(cuva_odnos_ivica, prema_vecoj_ivici, std::make_pair(skaliranje_height, skaliranje_width));
        
        //act
        snap::Slika* slika2 = sk.primeni(std::make_shared<snap::Slika>(s)).get();
        
        //assert
        REQUIRE(slika2->getHeight() == skaliranje_height);
        REQUIRE(slika2->getWidth() == skaliranje_width);
        
    }
}
