#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <random>
#include "json.hpp"

using json = nlohmann::json;



class JsonParser {

public:
    struct DataPoint {
        double time;
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
                    dp.time = item["time"].get<double>();
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

    std::list<double> getTimeList(const std::vector<DataPoint>& dataPoints) {
        std::list<double> timeList;

        for (const auto& dp : dataPoints) {
            timeList.push_back(dp.time);
        }

        return timeList;
    }

    std::vector<double> getTimeVector(const std::vector<DataPoint>& dataPoints) {
        std::vector<double> timeList;

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
            std::vector<std::vector<double>> data = jsonData["dataset_data"]["data"];

            for (const auto& item : data) {
                DataPoint dp;
                dp.time = item[0];
                dp.open = item[1];
                dp.high = item[2];
                dp.low = item[3];
                dp.close = item[4];
                //dp.volumeFrom = item[];
                dp.volumeTo = item[5];


                dataPoints.push_back(dp);
            }

        } catch (const json::exception& e) {
            std::cerr << "JSON parsing error: " << e.what() << std::endl;
        }

        return dataPoints;
    }

};



class NamePars
{
public:
    std::vector<std::string> parseNames(const std::string& jsonStr) {
        std::vector<std::string> cryptos;

        try {
            json jsonData = json::parse(jsonStr);
            json data = jsonData["Data"];

            for (auto it = data.begin(); it != data.end(); ++it) {
                cryptos.push_back(it.key());
            }
        }
        catch (const json::exception& e) {
            std::cerr << "JSON parsing error: " << e.what() << std::endl;
        }
        std::vector<std::string> smallerVector;
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_real_distribution<double> dis(0.0, 1.0);
        double reductionFactor = 0.002; // Factor of 100 reduction

        for (const auto& element : cryptos) {

            if (dis(gen) <= reductionFactor) {
                smallerVector.push_back(element);
            }
        }

        return smallerVector;
    }
};
