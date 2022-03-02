#include <chrono>
#include <string>
#include <ctime>

#include "Time.hpp"

double Time::Since(Time* t)
{
    std::chrono::duration<double> elapsed = Now() - t->GetStartedAt();

    return elapsed.count();
}

std::string Time::String()
{
    std::time_t tt = std::chrono::system_clock::to_time_t(_startedAt);
    auto lc = localtime(&tt);
    char ts[] = {0};
    strftime(ts, 20, "%Y-%m-%d %H:%M:%S", lc);
    return std::string(ts);
}