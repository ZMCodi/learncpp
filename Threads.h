#include <iostream>
#include <thread>
#include <chrono>
#include <semaphore>
#include <sstream>
#include <atomic>
#include "Random.h"

using secs = std::chrono::seconds;
void sleep(int min, int max, secs sec = secs{0}) 
{
    if (sec == secs{0})
    {
        std::this_thread::sleep_for(secs{Random::get(min, max)});
    } else
    {
        std::this_thread::sleep_for(sec);
    }
}
