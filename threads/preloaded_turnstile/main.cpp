#include <vector>
#include "../../Threads.h"

// same thing as double turnstile but instead of
// sequentially locking and unlocking, the last thread
// preload the turnstile with however many threads need to pass
std::counting_semaphore<5> turnstile{0};
std::counting_semaphore<5> turnstile2{0}; // starts locked here

std::mutex mutex;
int friendsArrived{0};

void themePark(char id)
{
    while (true)
    {
        std::stringstream msg;
        // driving
        msg << "Friend " << id << " driving to theme park" << std::endl;
        std::cout << msg.str();
        if (id != 'J')
            sleep(2, 10);

        // friend signal that it has arrived
        msg.str("");
        msg << "Friend " << id << " has arrived at theme park" << std::endl;
        std::cout << msg.str();

        {
            std::lock_guard lock(mutex);
            ++friendsArrived;

            // after the final friend comes, they all go in the
            // theme park through a turnstile
            if (friendsArrived == 5)
            {
                // unlocks for 5 threads at once
                turnstile.release(5);
            }
        }

        // each thread locks, the final thread effectively locking
        // the turnstile again
        turnstile.acquire();

        // no need to release here since turnstile is preloaded

        msg.str("");
        msg << "Friend " << id << " is in the theme park" << std::endl;
        std::cout << msg.str();
        if (id != 'J') // J doesn't like theme parks very much
            sleep(2, 6);

        msg.str("");
        msg << "Friend " << id << " is done playing and waiting at the exit" << std::endl;
        std::cout << msg.str();

        {
            std::lock_guard lock(mutex);
            --friendsArrived;

            // last thread preloads turnstile to allow 5 threads to pass
            if (friendsArrived == 0)
            {
                turnstile2.release(5);
            }
        }

        // last thread passing effectively locks the turnstile
        turnstile2.acquire();

        // day has ended, come back again tomorrow
        if (id == 'J')
        {
            msg.str("");
            std::cout << "E << std::endlOD, lets come back again tomorrow" << std::endl;
        }
        sleep(0, 0, secs{5});
    }

}

int main()
{
    std::vector<std::thread> friends{};
    friends.reserve(5);

    for (int i{}; i < 5; ++i)
    {
        friends.emplace_back(themePark, static_cast<char>(74 + i));
    }

    for (auto& f : friends)
    {
        f.join();
    }
}
