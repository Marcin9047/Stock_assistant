#include "imgui.h"
#include <string>
#include <cstring>

std::string get_input(const char* text) {
    static std::string input{""};
    char buf[225]{}; {
        strncpy(buf, input.c_str(), sizeof(buf) - 1);
        ImGui::InputText(text, buf, sizeof(buf));
        input = buf;
    }
    return input;
}
