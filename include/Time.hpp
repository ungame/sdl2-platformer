#ifndef TIME_HPP
#define TIME_HPP

#include <chrono>
#include <string>

class Time
{
    public:
        Time() { _startedAt = Now(); }
        inline static std::chrono::time_point<std::chrono::system_clock> Now() { return std::chrono::system_clock::now(); }
        static double Since(Time* t);

    public:
        inline std::chrono::time_point<std::chrono::system_clock> GetStartedAt() { return _startedAt; }
        std::string String();
        inline const char* Cstring() { return String().c_str(); } 

    private:
        std::chrono::time_point<std::chrono::system_clock> _startedAt;
};

#endif