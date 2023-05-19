#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>

bool isrising(const std::vector<double>& inputArray)
{

    double result =0.0;
    if (inputArray.size() < 2) {
        std::cout << "Tablica wejściowa musi mieć co najmniej 2 elementy!" << std::endl;
        return false;
    }

    std::vector<double> currentArray = inputArray;

    while (currentArray.size() > 2) {
        std::vector<double> newArray;

        for (size_t i = 0; i < currentArray.size() - 1; i++) {
            double average = (currentArray[i] + currentArray[i + 1]) / 2;
            newArray.push_back(average);
        }

        currentArray = newArray;
    }

    result = currentArray[1] - currentArray[0];

    if (result>0)
    {
        return true;
    }
    return false ;
};

double recentdiff(const std::vector<double>& values) {

    int size = values.size();
    if (size < 4) {
        std::cerr << "Wektor musi zawierać przynajmniej 4 wartości!" << std::endl;
        return 0.0;
    }

    double sum = 0.0;
    for (int i = size - 2; i >= size - 4; --i) {
        sum += values[i];
    }
    double average = sum / 3.0;
    double lastValue = values[size - 1];
    double difference = lastValue - average;
    return difference;
}

TEST_CASE("isrising method")
{
    SECTION("isrising - empty array")
    {
        std::vector<double> emptyArray;
        REQUIRE(!isrising(emptyArray));
    }

    SECTION("isrising - array with one element")
    {
        std::vector<double> array = {1.0};
        REQUIRE(!isrising(array));
    }

    SECTION("isrising - array with two elements (not rising)")
    {
        std::vector<double> array = {3.0, 2.0};
        REQUIRE(!isrising(array));
    }

    SECTION("isrising - array with two elements (rising)")
    {
        std::vector<double> array = {2.0, 3.0};
        REQUIRE(isrising(array));
    }

    SECTION("isrising - array with more than two elements (not rising)")
    {
        std::vector<double> array = {5.0, 4.0, 2.0, 1.0};
        REQUIRE(!isrising(array));
    }

    SECTION("isrising - array with more than two elements (rising)")
    {
        std::vector<double> array = {1.0, 2.0, 3.0, 4.0};
        REQUIRE(isrising(array));
    }

    SECTION("isrising - array with more than two elements (not continuously rising)")
    {
        std::vector<double> array = {1.0, 3.0, 2.0, 4.0};
        REQUIRE(isrising(array));
        array.clear();
        array = {1.0, 3.0, 0.0, 2.0};
        REQUIRE(!isrising(array));
    }
}

TEST_CASE("recentdiff method") {
    SECTION("increased") {
        std::vector<double> values = {1.0, 2.0, 3.0, 4.0, 5.0};
        double result = recentdiff(values);
        REQUIRE(result == Approx(2.0));
    }

    SECTION("decreased") {
        std::vector<double> values = {5.0, 4.0, 3.0, 2.0, 1.0};
        double result = recentdiff(values);
        REQUIRE(result == Approx(-2.0));
    }
}

