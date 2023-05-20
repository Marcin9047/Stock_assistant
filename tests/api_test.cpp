#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/api/api.h"
#include "../src/api/api_cc.h"

TEST_CASE("Api class") {
    SECTION("get_data() returns a string if url is correct") {
        std::string test_url = "https://min-api.cryptocompare.com/data/price?fsym=BTC&tsyms=PLN";
        Api api(test_url);
        std::string data = api.get_data();
        REQUIRE(!data.empty());
    }
    SECTION("get_data returns an empty string if url is incorrect") {
        std::string test_url = "https://notexistingurl.com/data/";
        Api api(test_url);
        std::string data = api.get_data();
        REQUIRE(data.empty());
    }
}

TEST_CASE("ApiCC class") {
    SECTION("Actual price test") {
        ApiCC api_cc;
        api_cc.set_type("single");
        api_cc.set_crypto("SOL");
        api_cc.set_currency("PLN");
        std::string data = api_cc.get_data();
        REQUIRE(!data.empty());
    }
}