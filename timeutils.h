#pragma once

#include <chrono>
#include <string>
#include <sstream>

using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::minutes;
using std::chrono::minutes;
using std::chrono::duration_cast;
using centiseconds = std::chrono::duration<long long, std::centi>;
using deciseconds = std::chrono::duration<long long, std::deci>;


enum class TimeUnit {
    milliseconds,
    centiseconds,
    deciseconds,
    seconds
};


struct MinSecMs {
    minutes minute;
    seconds sec;
    milliseconds ms;

    MinSecMs(milliseconds time)
    {
        minute = duration_cast<minutes>(time);
        sec = duration_cast<seconds>(time - minute);
        ms = duration_cast<milliseconds>(time - minute - sec);
    }
    std::string to_string()
    {
        std::stringstream ss;
        ss << minute.count() << "'" << sec.count() << "''" << ms.count();
        return ss.str();
    }
};

std::string TimeUnitToString(TimeUnit unit)
{
    switch (unit)
    {
    case TimeUnit::milliseconds:
        return "milliseconds";
    case TimeUnit::centiseconds:
        return "centiseconds";
    case TimeUnit::deciseconds:
        return "deciseconds";
    case TimeUnit::seconds:
        return "seconds";
    }
    return "";
}