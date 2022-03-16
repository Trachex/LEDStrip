#include "log.hpp"

Logger::Logger(string sourceComp) {
    source = sourceComp;
}

void Logger::logln(string arg) {
    Serial.println(source.toArduinoString() + ": " + arg.toArduinoString());
}

void Logger::logln(int arg) {
    Serial.println(source.toArduinoString() + ": " + arg);
}

void Logger::logf(string format, string args...) {
    string tmpFormat = "%d: " + format + "\n";
    Serial.printf(tmpFormat.c_str(), source, args);
}