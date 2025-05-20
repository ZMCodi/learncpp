#include "../../Threads.h"

// you and bob live in different cities. how do you ensure that you eat lunch before bob
// if bob can (and will) follow instructions. well just tell bob to wait for a call before
// having lunch and you call him after you've had lunch. this code simulates that

bool called = false;

void you()
{
    std::cout << "You: Eat breakfast\n";
    sleep(0, 0, secs{1});
    std::cout << "You: Work\n";
    sleep(0, 0, secs{2});
    std::cout << "You: Eat lunch\n";
    sleep(0, 0, secs{1});
    std::cout << "You: Call Bob\n";
    called = true;
}

void bob()
{
    std::cout << "Bob: Eat breakfast\n";
    sleep(0, 0, secs{1});
    std::cout << "Bob: Wait for a call\n";
    while (!called)
    ; // do nothing
    std::cout << "Bob: Eat lunch\n";
}

int main()
{
    std::thread Bob{bob};
    std::thread You{you};

    You.join();
    Bob.join();
}
