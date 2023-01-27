#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <cstdlib>
#include <memory>
#include <string>
#include <algorithm>

#include "../inc/slika.hpp"
#include "../inc/skaliranje.hpp"
#include "../inc/isecanje.hpp"
#include "../inc/spajanje.hpp"
#include "../inc/enumi.hpp"

TEST_CASE("klasa slika", "[function]")
{
    
    SECTION("Sacuvaj na disku test")
    {
        // Arrange
        snap::Slika s("../resources/resources/heart.ico");

        // Act
        std::string path = "./slika.ico";
        s.sacuvajNaDisku(path);

        // Assert
        snap::Slika s2("./slika.ico");
        REQUIRE(s2.getHeight() > 0);
        REQUIRE(s2.getWidth() > 0);
    }
    
    SECTION("Skaliraj sliku")
    {
        //arrange
        snap::Slika s("../resources/resources/heart.png");
        const auto skaliranje_height = rand() % s.getHeight();
        const auto skaliranje_width = rand() % s.getWidth();
        const auto current_width = s.getWidth();
        const auto current_height = s.getHeight();
                
        const bool cuva_odnos_ivica = false;
        const bool prema_vecoj_ivici = (rand() % 2 == 0 ? true : false);
        
                
        //act
        s.skaliraj(cuva_odnos_ivica, prema_vecoj_ivici, std::make_pair(skaliranje_height, skaliranje_width));
        
        
        //assert
        REQUIRE(s->getHeight() == skaliranje_height);
        REQUIRE(s->getWidth() == skaliranje_width);
        
    }
    
    SECTION("Iseci sliku")
    {
        //arrange
        snap::Slika s("../resources/resources/heart.png");
        auto gornja_leva_height = rand() % s.getHeight();
        auto gornja_leva_width = rand() % s.getWidth();
        
        auto donja_desna_height = rand() % s.getHeight();
        auto donja_desna_width = rand() % s.getWidth();
        
        if(gornja_leva_height < donja_desna_height)
            std::swap(gornja_leva_height,donja_desna_height);
        if(gornja_leva_width > donja_desna_width)
            std::swap(gornja_leva_width, donja_desna_width);
        
        //act
        s.iseci(std::make_pair(gornja_leva_height, gornja_leva_width),
                std::make_pair(donja_desna_height, donja_desna_width));
        
            
        //assert
        REQUIRE(s->getHeight() == gornja_leva_height - donja_desna_height);
        REQUIRE(s->getWidth() == gornja_leva_width - donja_desna_width);
        
    }
    
    SECTION("Zalepi sliku") 
    {
        //arrange
        snap::Slika s("../resources/resources/heart.png");
        snap::Slika s1("../resources/resources/heart.png"");
        
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
        Poravnanje poravnanje = Poravnanje::CENTER;

        //act
        s.zalepi(std::make_shared<snap::Slika>(s1), horiz, poravnanje,pozadina);
        
                
        //assert
        REQUIRE(s->getHeight() == desired_height);
        REQUIRE(s->getWidth() == desired_width);
    }
    
}

