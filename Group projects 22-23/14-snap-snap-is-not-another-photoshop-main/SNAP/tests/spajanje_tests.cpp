#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <cstdlib>

#include "../inc/spajanje.hpp"
#include "../inc/slika.hpp"
#include "../inc/enumi.hpp"


TEST_CASE("klasa spajanje", "[function]")
{

    SECTION("Zalepi slike") 
    {
        //arrange
        snap::Slika s("../resources/resources/heart.ico");
        snap::Slika s1("../resources/resources/heart.ico");
        
        const bool obrnutim_redosledom = (rand() % 2 == 0 ? true : false);
        const bool horiz = (rand() % 2 == 0 ? true : false);
        
        int desired_height, desired_width;
        
        if(horiz){
            desired_height = s.getHeight() > s1.getHeight()  ? s.getHeight() : s1.getHeight();
            desired_width = s.getWidth() + s1.getWidth();
        }
        else {
            desired_height = s.getHeight() + s1.getHeight();
            desired_width = s.getWidth() > s1.getWidth()  ? s.getWidth() : s1.getWidth();
        }
        
        std::string pozadina = "red";
        Poravnanje poravnjanje = Poravnanje::CENTER;

        snap::spajanje spaj(horiz, obrnutim_redosledom, poravnjanje, pozadina);
        
        //act
        snap::Slika* s2 = spaj.primeni(std::make_shared<snap::Slika>(s), std::make_shared<snap::Slika>(s1)).get();
        
        //assert
        REQUIRE(s2->getHeight() == desired_height);
        REQUIRE(s2->getWidth() == desired_width);
    }
    
}
