#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;



class JsonParser {

public:
    struct DataPoint {
        std::string time;
        double open;
        double high;
        double low;
        double volumeFrom;
        double volumeTo;
        double close;
    };

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

    std::list<std::string> getTimeList(const std::vector<DataPoint>& dataPoints) {
        std::list<std::string> timeList;

        for (const auto& dp : dataPoints) {
            timeList.push_back(dp.time);
        }

        return timeList;
    }

    std::list<double> getOpenList(const std::vector<DataPoint>& dataPoints) {
        std::list<double> openList;

        for (const auto& dp : dataPoints) {
            openList.push_back(dp.open);
        }

        return openList;
    }

    std::list<double> getHighList(const std::vector<DataPoint>& dataPoints) {
        std::list<double> highList;

        for (const auto& dp : dataPoints) {
           highList.push_back(dp.high);
        }

        return highList;
    }

    std::list<double> getLowList(const std::vector<DataPoint>& dataPoints) {
        std::list<double> lowList;

        for (const auto& dp : dataPoints) {
           lowList.push_back(dp.low);
        }

        return lowList;
    }

    std::list<double> getVolumeFromList(const std::vector<DataPoint>& dataPoints) {
        std::list<double> volumeFromList;

        for (const auto& dp : dataPoints) {
           volumeFromList.push_back(dp.volumeFrom);
        }

        return volumeFromList;
    }

    std::list<double> getVolumeToList(const std::vector<DataPoint>& dataPoints) {
        std::list<double> volumeToList;

        for (const auto& dp : dataPoints) {
           volumeToList.push_back(dp.volumeTo);
        }

        return volumeToList;
    }

    std::list<double> getCloseList(const std::vector<DataPoint>& dataPoints) {
        std::list<double> closeList;

        for (const auto& dp : dataPoints) {
           closeList.push_back(dp.close);
        }

        return closeList;
    }

    std::vector<double> getCloseVector(const std::vector<DataPoint>& dataPoints) {
        std::vector<double> closeList;

        for (const auto& dp : dataPoints) {
           closeList.push_back(dp.close);
        }

        return closeList;
    }

    std::vector<double> getOpenVector(const std::vector<DataPoint>& dataPoints) {
        std::vector<double> openList;

        for (const auto& dp : dataPoints) {
            openList.push_back(dp.open);
        }

        return openList;
    }

    std::vector<double> getHighVector(const std::vector<DataPoint>& dataPoints) {
        std::vector<double> highList;

        for (const auto& dp : dataPoints) {
           highList.push_back(dp.high);
        }

        return highList;
    }

    std::vector<double> getLowVector(const std::vector<DataPoint>& dataPoints) {
        std::vector<double> lowList;

        for (const auto& dp : dataPoints) {
           lowList.push_back(dp.low);
        }

        return lowList;
    }

    std::vector<double> getVolumeFromVector(const std::vector<DataPoint>& dataPoints) {
        std::vector<double> volumeFromList;

        for (const auto& dp : dataPoints) {
           volumeFromList.push_back(dp.volumeFrom);
        }

        return volumeFromList;
    }

    std::vector<double> getVolumeToVector(const std::vector<DataPoint>& dataPoints) {
        std::vector<double> volumeToList;

        for (const auto& dp : dataPoints) {
           volumeToList.push_back(dp.volumeTo);
        }

        return volumeToList;
    }

};


class NASDAQ_pars :public JsonParser
{
public:

    std::vector<DataPoint> parse_NASDAQ(const std::string& jsonStr)
    {
        std::vector<DataPoint> dataPoints;

        try {
            json jsonData = json::parse(jsonStr);

            if (jsonData["Response"] == "Success") {//to be changed
                json data = jsonData["Data"]["Data"];//to be changed

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

    std::list<std::string> getTimeList(const std::vector<JsonParser::DataPoint>& dataPoints)
    {
        JsonParser::getTimeList(dataPoints);
    }

    std::list<double> getOpenList(const std::vector<DataPoint>& dataPoints) {
        JsonParser::getOpenList(dataPoints);

    }

    std::list<double> getHighList(const std::vector<DataPoint>& dataPoints) {
        JsonParser::getHighList(dataPoints);

    }

    std::list<double> getLowList(const std::vector<DataPoint>& dataPoints) {
        JsonParser::getLowList(dataPoints);

    }

    std::list<double> getVolumeFromList(const std::vector<DataPoint>& dataPoints) {
        JsonParser::getVolumeFromList(dataPoints);

    }

    std::list<double> getVolumeToList(const std::vector<DataPoint>& dataPoints) {
        JsonParser::getVolumeToList(dataPoints);

    }

    std::list<double> getCloseList(const std::vector<DataPoint>& dataPoints) {
        JsonParser::getCloseList(dataPoints);

    }

    std::vector<double> getCloseVector(const std::vector<DataPoint>& dataPoints) {
        JsonParser::getCloseVector(dataPoints);

    }

    std::vector<double> getOpenVector(const std::vector<DataPoint>& dataPoints) {
        JsonParser::getOpenVector(dataPoints);

    }

    std::vector<double> getHighVector(const std::vector<DataPoint>& dataPoints) {
        JsonParser::getHighVector(dataPoints);

    }

    std::vector<double> getLowVector(const std::vector<DataPoint>& dataPoints) {
        JsonParser::getLowVector(dataPoints);

    }

    std::vector<double> getVolumeFromVector(const std::vector<DataPoint>& dataPoints) {
        JsonParser::getVolumeFromVector(dataPoints);

    }

    std::vector<double> getVolumeToVector(const std::vector<DataPoint>& dataPoints) {
        JsonParser::getVolumeToVector(dataPoints);

    }

};