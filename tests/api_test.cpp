#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/api/api.h"

TEST_CASE("Api class") {
    SECTION("get_data returns a string") {
        std::string test_url = "https://min-api.cryptocompare.com/data/price?fsym=BTC&tsyms=PLN";
        Api api(test_url);
        std::string data = api.get_data();
        REQUIRE(!data.empty());
    }
}