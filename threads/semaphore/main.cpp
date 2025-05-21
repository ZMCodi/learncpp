#include <vector>
#include "../../Threads.h"

// demo for semaphore. 5 office workers are working and sometimes they go
// on toilet breaks. however, there are only 3 stalls so if they are full
// (i.e. semaphore is 0) then they have to go back to work and only if 
// someone leaves the toilet can they try and go again

// only 3 stalls in the office
std::counting_semaphore<3> toilet(3);
std::atomic<int> working{};

void work(int id)
{
    ++working;
    while (true)
    {
        // workers start off working
        std::stringstream message;
        message << "Worker " << id << " is working" << std::endl;
        std::cout << message.str();
        sleep(5, 10); // simulate working

        // time for toilet break
        message.str("");
        message << "Worker " << id << " is going for a toilet break" << std::endl;
        std::cout << message.str();
        --working;

        // check if toilet is empty
        if (toilet.try_acquire())
        {
            message.str("");
            message << "Toilet is empty. Worker " << id << " is relieving himself" << std::endl;
            std::cout << message.str();
            sleep(2, 3); // simulate relieving

            message.str("");
            message << "Worker " << id << " is done with toilet break. Going back to work :D" << std::endl;
            std::cout << message.str();
            toilet.release();
        } else
        {
            // we could make them get into a queue here but this is an intro program
            // so we'll just make them go back to work holding their urges
            message.str("");
            message << "Toilet is full. Worker " << id << " is returning back to work :(" << std::endl;
            std::cout << message.str();
        }

        ++working;
    }
}

void monitor()
{
    while (true)
    {
        std::stringstream message;
        message << working << " workers working" << std::endl;
        std::cout << message.str();
        sleep(0, 0, secs{2}); // update every two seconds
    }
}

int main()
{
    std::vector<std::thread> workers{};
    workers.reserve(5);

    std::thread Monitor(monitor);
    for (int i{1}; i <= 5; ++i)
    {
        sleep(0, 0, secs{1}); // stagger workers coming in
        workers.emplace_back(work, i);
    }

    for (auto& worker : workers)
    {
        worker.join();
    }

    Monitor.join();
}
