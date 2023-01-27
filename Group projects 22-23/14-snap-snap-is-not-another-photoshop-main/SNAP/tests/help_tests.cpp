#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <string>

#include "../inc/help.hpp"

TEST_CASE("klasa help", "[function]")
{   
    SECTION("Help validno ucitava help fajl")
    {
        // Arrange
        Help h{};

        // Act
        std::string help_string = h.getHelp();
        
        // Assert
        REQUIRE(help_string.length() > 0);
    }
    
    SECTION("Help validno ucitava about fajl")
    {
        // Arrange
        Help h{};

        // Act
        std::string about_string = h.getAbout();
        
        // Assert
        REQUIRE(about_string.length() > 0);
    }
    
    SECTION("Help u polju help ima string upisan u fajl help.txt") 
    {
        //arrange
        Help h{};
        
        //act
        std::string help_string = h.getHelp();
        
        std::ifstream f;
        f.open("../help.txt");
        std::string help_from_file, line;
        while (std::getline(f, line)){
            help_from_file += line;
        }
        f.close();
        
        //assert
        REQUIRE(help_string == help_from_file);
        
        
    }
    
    SECTION("Help u polju about ima string upisan u fajl about.txt") 
    {
        //arrange
        Help h{};
        
        //act
        std::string about_string = h.getAbout();
        
        std::ifstream f;
        f.open("../about.txt");
        std::string line, about_from_file;
        while (std::getline(f, line)){
            about_from_file += line;
        }
        
        //assert
        REQUIRE(about_string == about_from_file);
    }
    
    
    
    
    
}
