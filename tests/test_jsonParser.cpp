#include<iostream>
#include "catch.hpp"
#include <list>
#include <vector>
#include <string>
#include "../src/sort/json.hpp"
#include "../src/sort/JsonFile.h"
#include "../src/sort/JsonParser.hpp"
#include "../src/sort/sort.h"
#include "../src/api/api_cc.h"
#include "../src/api/api.h"

using json = nlohmann::json;
using DataPoint = JsonParser::DataPoint;

TEST_CASE("Extracting time array") {
    JsonParser parser;

    SECTION("Get time array from data points") {
        std::vector<DataPoint> dataPoints{
            {1681420800, 30662.12, 30080.89, 30399.03, 32303.34, 980402944.59, 30493.01},
            {1681507200, 30930.91, 30468.7, 30493.01, 28606.07, 877428149.57, 30681.3},
            {1681603200, 30966.6, 30322.4, 30681.3, 26399.09, 812994387.5, 30943.7}
        };

        std::list<double> expectedTimeArray{1681420800, 1681507200, 1681603200};

        std::list<double> actualTimeArray = parser.getTimeList(dataPoints);

        REQUIRE(actualTimeArray == expectedTimeArray);
    }

    SECTION("Get time array from empty data points") {
        std::vector<DataPoint> dataPoints;

        std::list<double> expectedTimeArray;

        std::list<double> actualTimeArray = parser.getTimeList(dataPoints);

        REQUIRE(actualTimeArray == expectedTimeArray);
    }
}

TEST_CASE("Get close vector")
{
    JsonParser parser;
    SECTION("Get close vector from data points")
    {
        std::vector<DataPoint> dataPoints{
            {1681420800, 30662.12, 30080.89, 30399.03, 32303.34, 980402944.59, 30493.01},
            {1681507200, 30930.91, 30468.7, 30493.01, 28606.07, 877428149.57, 30681.3},
            {1681603200, 30966.6, 30322.4, 30681.3, 26399.09, 812994387.5, 30943.7}
        };

        std::vector<double> expectedCloseVector{30493.01, 30681.3, 30943.7};

        std::vector<double> actualCloseVector = parser.getCloseVector(dataPoints);

        REQUIRE(actualCloseVector == expectedCloseVector);
    }
}

TEST_CASE("constructor")
{
    SECTION("BTC")
    {
        std::string currency="USD";
        std::string type = "daily";
        std::string crypto = "BTC";
        JsonParser parser;
        ApiCC api;
        api.set_type(type);
        api.set_crypto(crypto);
        api.set_currency(currency);
        std::string jsonString = api.get_data();
        std::vector<DataPoint> dataPoints = parser.parseJSON(jsonString);
        std::vector<double> CloseVector = parser.getCloseVector(dataPoints);
        std::vector<double> OpenVector = parser.getOpenVector(dataPoints);
        std::vector<double> HighVector = parser.getHighVector(dataPoints);
        std::vector<double> LowVector = parser.getLowVector(dataPoints);
        REQUIRE(CloseVector.size()==31);
        REQUIRE(OpenVector.size()==31);
        REQUIRE(HighVector.size()==31);
        REQUIRE(LowVector.size()==31);

    }

    SECTION("Nameparser")
    {
        ApiCC api;
        api.set_type("symbols");
        std::string cryptos_names = api.get_data();
        NamePars name_parser;
        std::vector<std::string> crypto = name_parser.parseNames(cryptos_names);
        REQUIRE(crypto.size()<50);

    }
}

TEST_CASE("sort")
{
    SECTION("lowkey")
    {
        std::vector<std::string> fav;
        std::string att = "lowkey";
        sort a(1,att,fav);
        std::vector<brand_crypto> cryptos = a.best_match();
        std::string name = cryptos[0].get_brand();
        REQUIRE_FALSE(name.empty());


    }
        SECTION("risky")
    {
        std::vector<std::string> fav;
        std::string att = "risky";
        sort r(1,att,fav);
        std::vector<brand_crypto> r_cryptos = r.best_match();
        std::string r_name = r_cryptos[0].get_brand();
        REQUIRE_FALSE(r_name.empty());


    }
}








