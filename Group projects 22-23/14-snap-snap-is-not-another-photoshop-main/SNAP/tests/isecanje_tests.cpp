#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <cstdlib>

#include "../inc/isecanje.hpp"
#include "../inc/slika.hpp"


TEST_CASE("klasa isecanje", "[function]")
{
    
    SECTION("Iseci sliku")
    {
        //arrange
        snap::Slika s("../resources/resources/heart.ico");
        auto gornja_leva_height = rand() % s.getHeight();
        auto gornja_leva_width = rand() % s.getWidth();
        
        auto donja_desna_height = rand() % s.getHeight();
        auto donja_desna_width = rand() % s.getWidth();
        
        if(gornja_leva_height < donja_desna_height)
            std::swap(gornja_leva_height,donja_desna_height);
        if(gornja_leva_width > donja_desna_width)
            std::swap(gornja_leva_width, donja_desna_width);
        
        snap::isecanje is(std::make_pair(gornja_leva_height, gornja_leva_width),
                          std::make_pair(donja_desna_height, donja_desna_width));
        
        //act
        snap::Slika* slika2 = is.primeni(std::make_shared<snap::Slika>(s)).get();
        
        //assert
        REQUIRE(slika2->getHeight() == gornja_leva_height - donja_desna_height);
        REQUIRE(slika2->getWidth() == gornja_leva_width - donja_desna_width);
        
    }
    
}
