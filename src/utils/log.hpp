#pragma once

#include "utils/string.hpp"

class Logger {
    public:
        Logger(string sourceComp);
        void logln(string arg);
        void logln(int arg);
        void logf(string format, string args...);
    private:
        string source;
};