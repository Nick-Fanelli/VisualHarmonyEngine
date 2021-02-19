#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include "Utils.h"

static const char* ANSI_RESET = "\033[0m";
static const char* ANSI_RED = "\033[0;31m";
static const char* ANSI_RED_BOLD = "\033[1;31m";
static const char* ANSI_YELLOW = "\033[0;33m";
static const char* ANSI_YELLOW_BOLD = "\033[1;33m";
static const char* ANSI_GREEN = "\033[0;32m";
static const char* ANSI_GREEN_BOLD = "\033[1;32m";

struct Log {

    enum LogLevel {
        LogLevelError = 0, LogLevelWarn = 1, LogLevelInfo = 2
    };

    static void SetLogLevel(const LogLevel& level) { s_LogLevel = level; }
    static LogLevel GetLogLevel() { return s_LogLevel; }

    template<typename T>
    static void Info(const T& message) {
        if(s_LogLevel >= LogLevelInfo)
            std::cout << "[Harmony Engine Info]: " << message << std::endl;
    }

    template<typename T>
    static void Success(const T& message) {
        if(s_LogLevel >= LogLevelInfo)
            std::cout << ANSI_GREEN_BOLD << "[Harmony Engine Success]: " << ANSI_GREEN << message << ANSI_RESET << std::endl;
    }

    template<typename T>
    static void Warn(const T& message) {
        if(s_LogLevel >= LogLevelWarn)
            std::cout << ANSI_YELLOW_BOLD << "[Harmony Engine Warning]: " << ANSI_YELLOW << message << ANSI_RESET << std::endl;
    }

    template<typename T>
    static void Error(const T& message) {
        if(s_LogLevel >= LogLevelError)
            std::cout << ANSI_RED_BOLD << "[Harmony Engine Error]: " << ANSI_RED << message << ANSI_RESET << std::endl;
    }

    Log() = delete;
    ~Log() = delete;

private:
    static LogLevel s_LogLevel;
};