package com.harmonygames.harmonyengine;

public class Log {

    // Reset
    private static final String ANSI_RESET = "\033[0m";  // Text Reset

    // Regular Colors
    private static final String ANSI_BLACK = "\033[0;30m";   // BLACK
    private static final String ANSI_RED = "\033[0;31m";     // RED
    private static final String ANSI_GREEN = "\033[0;32m";   // GREEN
    private static final String ANSI_YELLOW = "\033[0;33m";  // YELLOW
    private static final String ANSI_BLUE = "\033[0;34m";    // BLUE
    private static final String ANSI_PURPLE = "\033[0;35m";  // PURPLE
    private static final String ANSI_CYAN = "\033[0;36m";    // CYAN
    private static final String ANSI_WHITE = "\033[0;37m";   // WHITE

    // Bold
    private static final String ANSI_BLACK_BOLD = "\033[1;30m";  // BLACK
    private static final String ANSI_RED_BOLD = "\033[1;31m";    // RED
    private static final String ANSI_GREEN_BOLD = "\033[1;32m";  // GREEN
    private static final String ANSI_YELLOW_BOLD = "\033[1;33m"; // YELLOW
    private static final String ANSI_BLUE_BOLD = "\033[1;34m";   // BLUE
    private static final String ANSI_PURPLE_BOLD = "\033[1;35m"; // PURPLE
    private static final String ANSI_CYAN_BOLD = "\033[1;36m";   // CYAN
    private static final String ANSI_WHITE_BOLD = "\033[1;37m";  // WHITE

    private static LogLevel logLevel = LogLevel.Info;

    public enum LogLevel {
        Error, Warn, Info
    }

    // ======================================================================
    //  Logging Methods
    // ======================================================================

    public static void fatalError(String message) {
        Log.error(message);
        System.exit(-1);
    }

    public static void error(String message) {
        if(logLevel.ordinal() >= LogLevel.Error.ordinal()) {
//            throw new RuntimeException(message);
            System.out.println(ANSI_RED_BOLD + "[Harmony Engine - Error]: " + ANSI_RED + message + ANSI_RESET);
        }
    }

    public static void warn(String message) {
        if(logLevel.ordinal() >= LogLevel.Warn.ordinal())
            System.out.println(ANSI_YELLOW_BOLD + "[Harmony Engine - Warning]: " + ANSI_YELLOW + message + ANSI_RESET);
    }

    public static void info(String message) {
        if(logLevel.ordinal() >= LogLevel.Info.ordinal())
            System.out.println("[Harmony Engine Info]: " + message);
    }

    public static void success(String message) {
        if(logLevel.ordinal() >= LogLevel.Info.ordinal())
            System.out.println(ANSI_GREEN_BOLD + "[Harmony Engine - Success]: " + ANSI_GREEN + message + ANSI_RESET);
    }

    public static void setLogLevel(LogLevel logLevel) { Log.logLevel = logLevel; }
    public static LogLevel getLogLevel() { return Log.logLevel; }
}