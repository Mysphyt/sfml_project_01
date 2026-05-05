#ifndef LOG_H
#define LOG_H

#include <string>
#include <sstream>
#include <iostream>
#include <SFML/Graphics.hpp>

enum LogLevel {
    SILENT,
    DEBUG 
};

const LogLevel LOG_LEVEL = DEBUG;

void Debug(std::string message); 

#endif