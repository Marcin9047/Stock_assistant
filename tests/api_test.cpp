#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/api/api.h"
#include "../src/api/api_cc.h"
#include "../src/api/api_nasdaq.h"
#include <nlohmann/json.hpp>

TEST_CASE("Api class tests") {
    SECTION("get_data() returns a non-empty string if url is correct") {
        std::string test_url = "https://min-api.cryptocompare.com/data/price?fsym=BTC&tsyms=PLN";
        Api api(test_url);
        std::string data = api.get_data();
        REQUIRE_FALSE(data.empty());
    }

    SECTION("get_data() throws std::runtime_error if url is incorrect") {
        Api api("https://notexistingurl.com/data/");
        REQUIRE_THROWS_AS(api.get_data(), std::runtime_error);
    }

    SECTION("get_data() throws std::runtime_error if url is empty") {
        Api api;
        REQUIRE_THROWS_AS(api.get_data(), std::runtime_error);
    }
}

TEST_CASE("ApiCC class tests") {
    SECTION("Get all symbols returns non-empty data"){
        ApiCC api_cc;
        api_cc.set_type("symbols");
        std::string data = api_cc.get_data();
        REQUIRE_FALSE(data.empty());
    }

    SECTION("Actual price test for single currency") {
        ApiCC api_cc;
        REQUIRE_THROWS_WITH(api_cc.set_type(""),"Type cannot be empty");
        REQUIRE_THROWS_WITH(api_cc.set_type("Single"),"Invalid type: Single");
        REQUIRE_THROWS_WITH(api_cc.set_type("monthly"),"Invalid type: monthly");
        REQUIRE_THROWS_WITH(api_cc.set_crypto(""),"Crypto cannot be empty");
        REQUIRE_THROWS_WITH(api_cc.set_currency(""),"Currency cannot be empty");

        api_cc.set_type("single");
        api_cc.set_crypto("SOL");
        api_cc.set_currency("PLN");
        std::string data = api_cc.get_data();
        REQUIRE_FALSE(data.empty());

        auto root = nlohmann::json::parse(data);
        REQUIRE_FALSE(root.is_null());
        REQUIRE(root.contains("PLN"));
    }

    SECTION("Historical prices test for daily data") {
        ApiCC api_cc;
        api_cc.set_type("daily");
        api_cc.set_crypto("SOL");
        api_cc.set_currency("PLN");
        std::string data = api_cc.get_data();
        REQUIRE_FALSE(data.empty());

        auto root = nlohmann::json::parse(data);
        REQUIRE_FALSE(root.is_null());
        REQUIRE(root["Response"].get<std::string>() == "Success");
        REQUIRE(root["HasWarning"].get<bool>() == false);
        REQUIRE(root.contains("Data"));
        REQUIRE(root["Data"].contains("Data"));
        REQUIRE(root["Data"]["Data"].is_array());
        REQUIRE(root["Data"]["Data"][0].contains("time"));
    }
}

TEST_CASE("ApiNasdaq class tests") {
    SECTION("nasdaq") {
        ApiNasdaq api_nasdaq;
        api_nasdaq.set_type("databases");
        // api_nasdaq.save_data_to_json();
        std::string data = api_nasdaq.get_data();
        REQUIRE_FALSE(data.empty());

        auto root = nlohmann::json::parse(data);
        REQUIRE_FALSE(root.is_null());
        REQUIRE(root.contains("databases"));
    }

    SECTION("api nasdaq ") {
        ApiNasdaq api_nasdaq;
        api_nasdaq.set_company("FB");
        api_nasdaq.set_database("WIKI");
        // api_nasdaq.save_data_to_json();
        std::string data = api_nasdaq.get_data();
        REQUIRE_FALSE(data.empty());

        auto root = nlohmann::json::parse(data);
        REQUIRE_FALSE(root.is_null());
        REQUIRE(root.contains("dataset_data"));
    }

    // SECTION("api nasdaq WARSAWSE") {
    //     ApiNasdaq api_nasdaq;
    //     api_nasdaq.set_database("WARSAWSE");
    //     api_nasdaq.set_company("MBANK");
    //     api_nasdaq.save_data_to_json();
    //     std::string data = api_nasdaq.get_data();
    //     REQUIRE_FALSE(data.empty());

    //     auto root = nlohmann::json::parse(data);
    //     REQUIRE_FALSE(root.is_null());
    //     REQUIRE(root.contains("dataset_data"));
    // }
}