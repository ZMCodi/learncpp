#include <exception>
#include "../../Threads.h"

// worker 1 and 2 watch over a nuclear reactor and they are free to take lunch breaks
// but both cant be at lunch at the same time or else no one is monitoring and
// reactor can (in this case will) go boom. What is the least number of messages that
// is required to ensure this never happens? Proposed answer is 1.

// start with 2 people watching the nuclear reactor
std::atomic<int> watcher{2};

// true: someone is at lunch
bool atLunch{false};

void worker(int id)
{
    while (true)
    {
        std::stringstream message;
        message << "Worker " << id << ": " << "Watching nuclear reactor\n";
        std::cout << message.str();
        sleep(5, 8);

        // DISCLAIMER: a TOCTOU might happen here
        // but since this is intro we'll let it slide
        // a proper implementation would use a mutex
        // lock instead of a bool

        // if someone is already at lunch
        while (atLunch)
        ; // wait

        // the other guy is now done with lunch
        atLunch = true;
        watcher--;
        message.str("");
        message << "Worker " << id << ": " << "Going to lunch\n";
        std::cout << message.str();

        // eating lunch
        sleep(2, 5);
        message.str("");
        message << "Worker " << id << ": " << "Finished with lunch\n";
        watcher++;
        atLunch = false;
    }
}

void monitor()
{
    while (true)
    {
        std::stringstream message;
        message << "Number of watchers: " << watcher << '\n';
        if (watcher <= 0)
        {
            // nuclear reactor goes boom
            throw std::runtime_error{"BOOM!!!"};
        }
        std::cout << message.str();
        sleep(0, 0, secs{1});
    }

}

int main()
{
    std::thread Monitor(monitor);
    std::thread worker1{worker, 1};
    std::thread worker2{worker, 2};

    Monitor.join();
    worker1.join();
    worker2.join();
}
