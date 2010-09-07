#include "Logger.h"

Logger::Logger() {

}

Logger::~Logger() {
    if (!_debug && _file) {
        _file.close();
    }
}

void Logger::Init() {
    _debug = false;
    if (!_debug) {
        _file.open("log.txt", std::ios::out | std::ios::trunc);
    }
}

void Logger::log(std::string message) {
    if (!_debug) {
        _file << message << std::endl;
    } else {
        std::cout << message << std::endl;
    }

}
