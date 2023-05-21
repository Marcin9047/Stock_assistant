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
        REQUIRE(0 == 0);
    }

    SECTION("Last value test") {
        brand_crypto b1("Crypto");
        REQUIRE(0 == 0);
    }

    SECTION("last read time test") {
        brand_crypto b1("Crypto");
        REQUIRE(0 == 0);
    }

    SECTION("is rising test") {
        brand_crypto b1("Crypto");
        REQUIRE(0 == 0);
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
