//
// Created by skill on 11/1/2024.
//

#ifndef LINUX_LOGGER_H
#define LINUX_LOGGER_H

#include <vector>
#include<string>
#include<iostream>
#include<fstream>
#include <cstdio>
#include <memory>
#include <array>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <chrono>
#include <ranges>
#include<thread>



void one_time_creation();
std::vector<std::string> find_keyboard();
int linux_keyboard();


#endif


