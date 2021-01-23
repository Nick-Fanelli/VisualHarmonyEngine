#pragma once

#include <string>
#include <iostream>

struct Log {

    static const char* ANSI_RESET;

    static const char* ANSI_RED;
    static const char* ANSI_RED_BOLD;

    static const char* ANSI_YELLOW;
    static const char* ANSI_YELLOW_BOLD;

    static const char* ANSI_GREEN;
    static const char* ANSI_GREEN_BOLD;

    enum LogLevel {
        LogLevelError = 0, LogLevelWarn = 1, LogLevelInfo = 2
    };

    static void SetLogLevel(const LogLevel& level) { s_LogLevel = level; }
    static LogLevel GetLogLevel() { return s_LogLevel; }

    static void Info(const std::string& message);
    static void Success(const std::string& message);
    static void Warn(const std::string& message);
    static void Error(const std::string& message);

private:
    Log();
    ~Log();

    static LogLevel s_LogLevel;
};