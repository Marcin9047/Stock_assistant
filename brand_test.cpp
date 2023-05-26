#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "brand.cpp"
#include "data.cpp"
#include "data.h"
#include "user.cpp"
#include <iostream>
#include <string>


TEST_CASE("Brand class") {
    SECTION("Get_brand name") {
        brand_crypto b1("Crypto");
        REQUIRE(b1.get_brand() == "Crypto");
    }

    SECTION("clear before test") {
        brand_crypto b1("Crypto");
        REQUIRE(0 == 0);
    }

    SECTION("<< operator test") {
        brand_crypto b1("Crypto");
        crypto_data d1(3221, 32.1, 12.3, 10, 21, 34, 15.7, '$');
        b1 << d1;
        REQUIRE(b1.last_read_time() == 3221);
    }

    SECTION(">> operator test") {
        brand_crypto b1("Crypto");
        crypto_data d1(3221, 32.1, 12.3, 10, 21, 34, 15.7, '$');
        b1 << d1;
        std::string s1;
        b1 >> s1;
        std::string result = "3221";
        result += " ";  // Dodaj przerwę za pomocą operatora konkatenacji
        result.append("15.70"); 
        REQUIRE(s1 == result);
    }

    SECTION("Last value test") {
        crypto_data d1(3221, 32.1, 12.3, 10, 21, 34, 15.7, '$');
        crypto_data d2(3321, 32.1, 12.3, 10, 21, 34, 17.5, '$');
        brand_crypto b1("Crypto");
        b1 << d1;
        b1 << d2;
        REQUIRE(b1.last_value() == 17.5);
    }

    SECTION("last read time test") {
        crypto_data d1(3221, 32.1, 12.3, 10, 21, 34, 15.7, '$');
        crypto_data d2(3321, 32.1, 12.3, 10, 21, 34, 17.5, '$');
        brand_crypto b1("Crypto");
        b1 << d1;
        b1 << d2;
        REQUIRE(b1.last_read_time() == 3321);
    }

    SECTION("is rising test") {
        brand_crypto b1("Crypto");
        crypto_data d1(3221, 32.1, 12.3, 10, 21, 34, 15.7, '$');
        crypto_data d2(3321, 32.1, 12.3, 10, 21, 34, 17.5, '$');
        b1 << d1;
        b1 << d2;
        REQUIRE(b1.is_rising() == true);
        crypto_data d3(3321, 32.1, 12.3, 10, 21, 34, 11.5, '$');
        b1 << d3;
        REQUIRE(b1.is_rising() == false);
    }
}

TEST_CASE("Data class")
{
    SECTION("get time test")
    {
        crypto_data d1(3221, 32.1, 12.3, 10, 21, 34, 15.7, '$');
        REQUIRE(d1.get_time() == 3221);
    }
    
    SECTION("get high value test")
    {
        crypto_data d1(3221, 32.1, 12.3, 10, 21, 34, 15.7, '$');
        REQUIRE(d1.get_high_value() == float(32.1));
    }

    SECTION("get low value test")
    {
        crypto_data d1(3221, 32.1, 12.3, 10, 21, 34, 15.7, '$');
        REQUIRE(d1.get_low_value() == float(12.3));
    }

    SECTION("test")
    {
        REQUIRE(0 == 0);
    }

    SECTION("test")
    {
        REQUIRE(0 == 0);
    }

    SECTION("test")
    {
        REQUIRE(0 == 0);
    }
}

TEST_CASE("User class")
{
   SECTION("capital test")
    {
        user u1;
        u1.set_capital(320);
        REQUIRE(u1.get_capital() == 320);
    }
}
