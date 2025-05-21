#include <vector>
#include "../../Threads.h"

// same thing as before but this time its in a loop
// so we have to ensure the turnstile is locked back
// after the last friend goes through but also no friend
// laps the others. they all wait at the exit before leaving
std::binary_semaphore turnstile{0};

// we need 2 turnstiles to ensure they loop again together
// and this starts unlocked
std::binary_semaphore turnstile2{1};

// instead of using atomic here lets use mutex bcs why not
std::mutex mutex;
int friendsArrived{0};

// in this case, J is a fast thread. It lives very close to the theme park
// and doesn't like to spend much time. we have to ensure J still waits
// to enter and exit the park with his friends
void themePark(char id)
{
    while (true)
    {
        std::stringstream msg;
        // driving
        msg << "Friend " << id << " driving to theme park" << std::endl;
        std::cout << msg.str();
        if (id != 'J') // J lives very close
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
                turnstile.release();
                // lock the second turnstile so they all leave together
                turnstile2.acquire();
            }
        }

        // other friends block here at the locked turnstile
        // only after the final friend unlocks the turnstile
        // can they pass through and lock it again
        turnstile.acquire();

        // as they pass through, unlock the turnstile for the next friend
        turnstile.release();

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

            // last guy locks the first turnstile for next loop
            // and unlocks the second turnstile so they all can leave
            if (friendsArrived == 0)
            {
                turnstile.acquire();
                turnstile2.release();
            }
        }

        // again lock and unlock
        turnstile2.acquire();
        turnstile2.release();

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
