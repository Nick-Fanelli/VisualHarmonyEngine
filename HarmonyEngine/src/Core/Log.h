#pragma once

#include <string>
#include <iostream>

struct Log {

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