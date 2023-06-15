#include "catch.hpp"
#include "../src/data/brand.h"
#include "../src/data/data.h"
#include "../src/data/user.h"
#include "../src/data/login.h"
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
        user_base sesion1("sesja1");
        user* u1 = new user("John3", "John_John", "8832");
        user* u2 = new user("John4", "John_John2", "8835");
        sesion1 % u1;
        sesion1 % u2;
        u1->set_capital(320);
        std::vector<user*> all = sesion1.get_users(); 
        REQUIRE(all.size() == 2);
    }

    SECTION("log_in test")
    {
        user_base sesion1("sesja1");
        user* u1 = new user("John", "John_John", "500");
        user* u2 = new user("John2", "John_John2", "8832");
        sesion1 % u1;
        sesion1 % u2;
        std::vector<std::string> data = {"John_John2" ,"8832"};
        user* u4 = sesion1 << data;
        REQUIRE(u4->get_name() == "John2");
        REQUIRE(u4->islogged() == true);
    }
    
    SECTION("log_in test")
    {
        user_base sesion1("sesja 1");
        user* u1 = new user("John", "John_John", "500");
        user* u2 = new user("John2", "John_John2", "8832");
        sesion1 % u1;
        sesion1 % u2;
        std::vector<std::string> data = {"John_John2" ,"8832"};
        user* u4 = sesion1 << data;
        sesion1 >> u4;
        sesion1.writeJsonToFile();
        REQUIRE(u4->islogged() == false);
    }

    SECTION("log_in test")
    {
        user_base sesion1("sesja 1");
        user* u1 = new user("John", "John_John", "500");
        user* u2 = new user("John2", "John_John2", "8832");


        brand_crypto b1("firma1");
        brand_crypto b2("firma2");
        brand_crypto b3("firma3");


        u1->add_favourite("firma1");
        u1->add_favourite("firma2");
        u1->add_favourite("firma3");


        sesion1 % u1;
        sesion1 % u2;


        sesion1.writeJsonToFile();
        user_base sesion2("sesja 1");
        sesion2.LoadFromJson();

        std::vector<std::string> data = {"John_John" ,"500"};
        user* u4 = sesion2 << data;


        std::vector<std::string> favorites = u4->get_favourites();
        for (int i; i < favorites.size(); i++)
        {
            std::cout << favorites[i];
        };

        std::vector<user*> all = sesion2.get_users();
        for (int i = 0; i < all.size(); i++)
        {
            std::cout << all.size();
            std::cout << all[i]->get_login();
            std::cout << all[i]->get_password();
        };

        
        REQUIRE(all.size() == 2);
        REQUIRE(favorites.size() == 3);
    }
}
