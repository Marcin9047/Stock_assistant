#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <list>
#include <vector>
#include <string>
#include "../sort/json.hpp"
#include "../sort/JsonParser.hpp"

using json = nlohmann::json;
using DataPoint = JsonParser::DataPoint;

TEST_CASE("Parsing JSON data", "[JSONParser]") {
    JsonParser parser;

    SECTION("Parse valid JSON data")
    {
        std::string jsonString = R"({
            "Data": [
                {
                    "time": "1681420800",
                    "high": 30662.12,
                    "low": 30080.89,
                    "open": 30399.03,
                    "volumefrom": 32303.34,
                    "volumeto": 980402944.59,
                    "close": 30493.01,
                    "conversionType": "direct",
                    "conversionSymbol": ""
                },
                {
                    "time": "1681507200",
                    "high": 30930.91,
                    "low": 30468.7,
                    "open": 30493.01,
                    "volumefrom": 28606.07,
                    "volumeto": 877428149.57,
                    "close": 30681.3,
                    "conversionType": "direct",
                    "conversionSymbol": ""
                },
                {
                    "time": "1681603200",
                    "high": 30966.6,
                    "low": 30322.4,
                    "open": 30681.3,
                    "volumefrom": 26399.09,
                    "volumeto": 812994387.5,
                    "close": 30943.7,
                    "conversionType": "direct",
                    "conversionSymbol": ""
                }
            ]
        })";

        std::vector<DataPoint> expectedDataPoints{
            {"1681420800", 30662.12, 30080.89, 30399.03, 32303.34, 980402944.59, 30493.01},
            {"1681507200", 30930.91, 30468.7, 30493.01, 28606.07, 877428149.57, 30681.3},
            {"1681603200", 30966.6, 30322.4, 30681.3, 26399.09, 812994387.5, 30943.7}
        };

        std::vector<DataPoint> actualDataPoints = parser.parseJSON(jsonString);

        REQUIRE(actualDataPoints == expectedDataPoints);
    }

    SECTION("Parse empty JSON data") {
        std::string jsonString = R"({ "Data": [] })";

        std::vector<DataPoint> expectedDataPoints;

        std::vector<DataPoint> actualDataPoints = parser.parseJSON(jsonString);

        REQUIRE(actualDataPoints == expectedDataPoints);
    }
}

TEST_CASE("Extracting time array", "[JSONParser]") {
    JsonParser parser;

    SECTION("Get time array from data points") {
        std::vector<DataPoint> dataPoints{
            {"1681420800", 30662.12, 30080.89, 30399.03, 32303.34, 980402944.59, 30493.01},
            {"1681507200", 30930.91, 30468.7, 30493.01, 28606.07, 877428149.57, 30681.3},
            {"1681603200", 30966.6, 30322.4, 30681.3, 26399.09, 812994387.5, 30943.7}
        };

        std::list<std::string> expectedTimeArray{"1681420800", "1681507200", "1681603200"};

        std::list<std::string> actualTimeArray = parser.getTimeList(dataPoints);

        REQUIRE(actualTimeArray == expectedTimeArray);
    }

    SECTION("Get time array from empty data points") {
        std::vector<DataPoint> dataPoints;

        std::list<std::string> expectedTimeArray;

        std::list<std::string> actualTimeArray = parser.getTimeList(dataPoints);

        REQUIRE(actualTimeArray == expectedTimeArray);
    }
}
