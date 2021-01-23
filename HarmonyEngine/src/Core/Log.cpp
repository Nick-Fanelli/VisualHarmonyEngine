#include "Log.h"

const char* Log::ANSI_RESET = "\033[0m";
const char* Log::ANSI_RED = "\033[0;31m";
const char* Log::ANSI_RED_BOLD = "\033[1;31m";
const char* Log::ANSI_YELLOW = "\033[0;33m";
const char* Log::ANSI_YELLOW_BOLD = "\033[1;33m";
const char* Log::ANSI_GREEN = "\033[0;32m";
const char* Log::ANSI_GREEN_BOLD = "\033[1;32m";

Log::LogLevel Log::s_LogLevel = Log::LogLevel::LogLevelInfo;

void Log::Info(const std::string& message) {
    if(s_LogLevel >= Log::LogLevelInfo)
        std::cout << "[Harmony Engine Info]: " << message << std::endl;
}

void Log::Success(const std::string& message) {
    if(s_LogLevel >= Log::LogLevelInfo)
        std::cout << ANSI_GREEN_BOLD << "[Harmony Engine Success]: " << ANSI_GREEN << message << ANSI_RESET << std::endl;
}

void Log::Warn(const std::string& message) { 
    if(s_LogLevel >= Log::LogLevelWarn)
        std::cout << ANSI_YELLOW_BOLD << "[Harmony Engine Warning]: " << ANSI_YELLOW << message << ANSI_RESET << std::endl;
}

void Log::Error(const std::string& message) {
    if(s_LogLevel >= Log::LogLevelError)
        std::cout << ANSI_RED_BOLD << "[Harmony Engine Error]: " << ANSI_RED << message << ANSI_RESET << std::endl;
}
