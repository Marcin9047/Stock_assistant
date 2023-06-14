#include "windows.h"
#include "../imgui/imgui.h"
#include "../imgui/my_widgets.h"
#include "../implot/implot.h"
#include "../implot/implot_internal.h"
#include "../implot/implot_candlestick.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>
#include "../../api/api.h"
#include "../../api/api_cc.h"
#include "../../api/api_nasdaq.h"

#include "../../data/data.h"
#include "../../data/brand.h"
#include "../../data/user.h"
#include "../../data/login.h"

#include "../../sort/JsonParser.hpp"
#include "../../sort/sort.h"

user current_user("123", "123", "123");
user_base users("sesja 1");

bool show_login_window;
bool show_profile_data;
bool show_stock;
bool show_registration;
bool show_login_error_window;

window::window(const char *title) {
    window_title = title;
}

void window::show() {
    ImGui::Begin(window_title);
    ImGui::End();
}

login_window::login_window() : window("Log in") {
}

void login_window::show()
{
    static bool load_session = true;
    if(load_session) {
        users.LoadFromJson();
        load_session = false;
    }
    static std::string login{""};
    static std::string password{""};
    ImGui::Begin(window_title);

    ImGui::Text("Please log in to start");
    char buf[255]{};
    {
        strncpy(buf, login.c_str(), sizeof(buf) - 1);
        ImGui::InputText("Login", buf, sizeof(buf));
        login = buf;
    }
    char buf2[255]{};
    {
        strncpy(buf2, password.c_str(), sizeof(buf2) - 1);
        ImGui::InputText("Password", buf2, sizeof(buf2));
        password = buf2;
    }

    if (ImGui::Button("Log in")) {
        std::vector<std::string> log_in_data;
        log_in_data.push_back(login);
        log_in_data.push_back(password);
        try{
            current_user = users<<log_in_data;
            show_profile_data = true;
            show_login_window = false;
        }
        catch (...) {
            show_login_window = false;
            show_login_error_window = true;
        }
        login = "";
        password = "";
        
    }
    if (ImGui::Button("Create account"))
    {
        show_registration = true;
        show_login_window = false;
    }

    ImGui::End();
}

profile_window::profile_window() : window("My profile")
{
}

void profile_window::show()
{
    ImGui::Begin(window_title);
    std::string name = "Name: ";
    const char *name_text = (name + current_user.get_name()).c_str();
    ImGui::Text("%s", name_text);
    std::string capital_text = "Capital " + std::to_string(current_user.get_capital());
    ImGui::Text("%s", capital_text.c_str());
    static bool update = false;
    if (ImGui::Button("Update capital"))
    {
        update = !update;
    }
    if (update) {
        static std::string capital{""};
        char buf[255]{};
        {
            strncpy(buf, capital.c_str(), sizeof(buf) - 1);
            ImGui::InputText("New capital", buf, sizeof(buf));
            capital = buf;
        }
        if (ImGui::Button("Update"))
        {
            current_user.set_capital(std::stoi(capital));
            capital = "";
        }
    }
    ImGui::Text("Search for stock");
    ImGui::Text("Choose attitude");
    std::vector<std::string> attitudes = {"Long-term investment", "Short-term investment"};
    static std::string attitude = "";
    if (ImGui::BeginCombo("##combo", attitude.c_str()))
    {
        for (size_t n = 0; n < attitudes.size(); n++)
        {
            bool is_selected = (attitude == attitudes[n]);

            if (ImGui::Selectable(attitudes[n].c_str(), is_selected))
                attitude = attitudes[n];
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }
    std::string att;
    static std::string selected_stock = "";
    if (!attitude.empty()) {
        int limit_multiplier;
        std::string type;
        if (attitude == "Long-term investment")
        {
            att = "lowkey";
            limit_multiplier = 1;
        }
        else if (attitude == "Short-term investment")
        {
            att = " ";
            limit_multiplier = 100;
        }
        type = "hourly";
        std::vector<std::string> favs = current_user.get_favourites();
        if (!favs.empty()) {
            
            if (ImGui::BeginCombo("##combo2", selected_stock.c_str())) {
                for (size_t n = 0; n < favs.size(); n++)
                {
                    bool is_selected = (selected_stock == favs[n]);

                    if (ImGui::Selectable(favs[n].c_str(), is_selected))
                        selected_stock = favs[n].c_str();
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
        }
        
        if (!selected_stock.empty()) {
            ApiCC req;
            req.set_type(type);
            req.set_crypto(selected_stock);
            req.set_currency("USD");
            std::string info = req.get_data();
            JsonParser parser;
            std::vector<JsonParser::DataPoint> dataPoints = parser.parseJSON(info);   
            std::vector<double> dates = parser.getTimeVector(dataPoints);
            std::vector<double> opens = parser.getOpenVector(dataPoints);
            std::vector<double> highs = parser.getHighVector(dataPoints);
            std::vector<double> lows = parser.getLowVector(dataPoints);
            std::vector<double> closes = parser.getCloseVector(dataPoints);

            const double *d_ptr = &dates[0];
            const double *o_ptr = &opens[0];
            const double *c_ptr = &closes[0];
            const double *l_ptr = &lows[0];
            const double *h_ptr = &highs[0];
            double limit_a = d_ptr[0];
            double limit_b = d_ptr[0];
            double limit_c = l_ptr[0];
            double limit_d = h_ptr[0];
            for (size_t i = 0; i < dates.size(); i++) {
                if (d_ptr[i] <  limit_a) limit_a = d_ptr[i];
                if (d_ptr[i] > limit_b) limit_b = d_ptr[i];
                if (l_ptr[i] <  limit_c) limit_c = l_ptr[i];
                if (h_ptr[i] > limit_d) limit_d = h_ptr[i];
            }
            static ImVec4 bullCol = ImVec4(0.000f, 1.000f, 0.441f, 1.000f);
            static ImVec4 bearCol = ImVec4(0.853f, 0.050f, 0.310f, 1.000f);
            // ImGui::SameLine(); ImGui::ColorEdit4("##Bull", &bullCol.x, ImGuiColorEditFlags_NoInputs);
            // ImGui::SameLine(); ImGui::ColorEdit4("##Bear", &bearCol.x, ImGuiColorEditFlags_NoInputs);
            ImPlot::GetStyle().UseLocalTime = false;

            static bool tooltip = true;
            ImGui::Checkbox("Show Tooltip", &tooltip);
            if (ImPlot::BeginPlot(selected_stock.c_str(), ImVec2(-1, 0))) {
                ImPlot::SetupAxes(nullptr, nullptr, 0, ImPlotAxisFlags_AutoFit | ImPlotAxisFlags_RangeFit);
                ImPlot::SetupAxesLimits(limit_a, limit_b, limit_c, limit_d);
                ImPlot::SetupAxisScale(ImAxis_X1, ImPlotScale_Time);
                ImPlot::SetupAxisLimitsConstraints(ImAxis_X1, limit_a, limit_b);
                ImPlot::SetupAxisZoomConstraints(ImAxis_X1, 60 * 60  * limit_multiplier, limit_b - limit_a);
                ImPlot::SetupAxisFormat(ImAxis_Y1, "$%.0f");
                MyImPlot::PlotCandlestick(selected_stock.c_str(), d_ptr, o_ptr, c_ptr, l_ptr, h_ptr, dates.size(), tooltip, 0.25f, bullCol, bearCol);
                ImPlot::EndPlot();
            }
        }
    }
    static bool add_stock = false;
    if (ImGui::Button("Add new stock"))
    {
        add_stock = !add_stock;
    }

    if (add_stock)
    {
        char buf[255]{};
        static std::string stock_name{""};
        {
            strncpy(buf, stock_name.c_str(), sizeof(buf) - 1);
            ImGui::InputText("##", buf, sizeof(buf));
            stock_name = buf;
        }
        ImGui::SameLine();
        if (ImGui::Button("Add"))
        {
            std::vector<std::string> favs = current_user.get_favourites();
            if (favs.empty() || std::count(favs.begin(), favs.end(), selected_stock)) current_user.add_favourite(stock_name);
            stock_name = "";
        }
    }
    if (ImGui::Button("Log out"))
    {
        selected_stock = "";
        attitude = "";
        show_profile_data = false;
        show_login_window = true;
    }
    ImGui::End();
}

registration_window::registration_window() : window("Create account")
{
}

void registration_window::show()
{
    ImGui::Begin(window_title);
    static std::string username{""};
    static std::string login{""};
    static std::string password{""};
    static std::string capital{""};
    

    char buf[225]{};
    {
        strncpy(buf, username.c_str(), sizeof(buf) - 1);
        ImGui::InputText("Username", buf, sizeof(buf));
        username = buf;
    }

    char buf2[255]{};
    {
        strncpy(buf2, login.c_str(), sizeof(buf2) - 1);
        ImGui::InputText("Login", buf2, sizeof(buf2));
        login = buf2;
    }

    char buf3[255]{};
    {
        strncpy(buf3, password.c_str(), sizeof(buf3) - 1);
        ImGui::InputText("Password", buf3, sizeof(buf3));
        password = buf3;
    }

    char buf4[255]{};
    {
        strncpy(buf4, capital.c_str(), sizeof(buf4) - 1);
        ImGui::InputText("Current capital", buf4, sizeof(buf4));
        capital = buf4;
    }
    if (ImGui::Button("Create account"))
    {
        user u(username, login, password, std::stoi(capital));
        std::vector<std::string> log_in_data;
        log_in_data.push_back(login);
        log_in_data.push_back(password);
        users%u;
        users<<log_in_data;
        users.writeJsonToFile();
        current_user = u;
        show_registration = false;
        show_profile_data = true;
    }
    if (ImGui::Button("Go back to logging in"))
    {
        users.writeJsonToFile();
        show_login_window = true;
        show_registration = false;
    }
    ImGui::End();
}

login_error_window::login_error_window() : window("Create account") {
}

void login_error_window::show() {
    ImGui::Begin(window_title);
    ImGui::Text("Wrong login or password");
    if (ImGui::Button("Try again")) {
        show_login_error_window = false;
        show_login_window = true;
    }
    ImGui::End();
}