//
// Created by ameer on 10/22/24.
//

#ifndef MAIN_HPP
#define MAIN_HPP



//determines the os this is import since this program is going to support windows and linux

inline int type_os()
{
#ifdef _WIN32
    return 1;
#elif defined(__unix__) || defined(__linux__)
    return 2;
#else
    return 0;
#endif

}


const char* exc(const char* cmd);


#endif //MAIN_HPP



