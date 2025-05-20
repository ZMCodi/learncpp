#include <vector>
#include "../../Threads.h"

// there are 5 friends who want to go to a theme park together
// they rendezvous together at the turnstile first before coming in
// this demo shows the turnstile pattern where a thread blocks a barrier
// then immediately unblocks it, letting the next thread through
std::binary_semaphore turnstile{0};
std::atomic<int> friendsArrived{0};

void themePark(char id)
{
    std::stringstream msg;
    // driving
    msg << "Friend " << id << " driving to theme park\n";
    std::cout << msg.str();
    sleep(2, 10);

    // friend signal that it has arrived
    msg.str("");
    msg << "Friend " << id << " has arrived at theme park\n";
    std::cout << msg.str();
    ++friendsArrived;

    // after the final friend comes, they all go in the
    // theme park through a turnstile
    if (friendsArrived == 5)
        turnstile.release();

    // other friends block here at the locked turnstile
    // only after the final friend unlocks the turnstile
    // can they pass through and lock it again
    turnstile.acquire();

    // as they pass through, unlock the turnstile for the next friend
    turnstile.release();

    msg.str("");
    msg << "Friend " << id << " is in the theme park\n";
    std::cout << msg.str();
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
