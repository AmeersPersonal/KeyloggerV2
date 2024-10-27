
#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <array>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <dirent.h>
/*
 * UNIX
 *
 *
 * PLAN
 *
 */

//determines the os
int type_os()
{
    #ifdef _WIN32
    return 1;
    #elif defined(__unix__) || defined(__linux__)
    return 2;
    #else
    return 0;
    #endif

}

//runs commands on the terminal
const char* exc(const char* cmd) {
    int os = type_os();

    switch (os) {
        case 0:
            throw std::exception();
            break;
        case 1:
            return "not made yet";
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


}

void one_time_creation() {
    std::fstream file;
    if(!file.is_open())
    {
        file.open("linux_devices", std::ios::in | std::ios::out | std::ios::trunc);

        file << exc("cat /proc/bus/input/devices");
        file.close();

    }
}





std::string find_keyboard() {
    const char* path = "/dev/input/bus/input/";

    DIR *dir = opendir(path);
    if(!dir) {
        std::cerr << "empty dir" <<std::endl;
        return "";
    }

    struct dirent *entry;

    while ((entry = readdir(dir))) {
        std::string file = entry->d_name;

        if (file.find("kbd") != std::string::npos) {
            closedir(dir);
            return path+file;
        }


    }


    return "";
}





int linux_keyboard()
{
    std::fstream file("test",std::ios::out | std::ios::app );

    const char* device_input = ("/dev/input/event0");
    int device = open(device_input, O_RDONLY);
    if(device == -1) {
        std::cerr << "HALP" << std::endl;
        return 1;

    }

    if(file.is_open()) {



        struct input_event ev;

        while (true){
            if(ssize_t r = read(device, &ev, sizeof(struct input_event)); r < static_cast<ssize_t>(sizeof(ev))) {
                return 1;
            }

            if(ev.type == EV_KEY) {
                std::cout << ev.code << std::endl;
                file << ev.code;
                file.flush();

            }

        }
    }
    close(device);
    file.close();
    return 0;
}





//todo
bool is_specia_key(int &key)
{
     switch (key)
     {
         case 1:
             std::cout << "TEST";
         break;


    }

}


int main() {
    one_time_creation();
    linux_keyboard();

    return 0;
}