#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

struct DataPoint {
    std::string time;
    double open;
    double high;
    double low;
    double volumeFrom;
    double volumeTo;
    double close;
};

class JsonParser {
public:
    std::vector<DataPoint> parseJSON(const std::string& jsonStr) {
        std::vector<DataPoint> dataPoints;

        try {
            json jsonData = json::parse(jsonStr);

            if (jsonData["Response"] == "Success") {
                json data = jsonData["Data"]["Data"];

                for (const auto& item : data) {
                    DataPoint dp;
                    dp.time = item["time"].dump();
                    dp.open = item["open"].get<double>();
                    dp.high = item["high"].get<double>();
                    dp.low = item["low"].get<double>();
                    dp.volumeFrom = item["volumefrom"].get<double>();
                    dp.volumeTo = item["volumeto"].get<double>();
                    dp.close = item["close"].get<double>();

                    dataPoints.push_back(dp);
                }
            }
        } catch (const json::exception& e) {
            std::cerr << "JSON parsing error: " << e.what() << std::endl;
        }

        return dataPoints;
    }
};
