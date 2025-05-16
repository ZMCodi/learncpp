#include <iostream>
#include <thread>
#include <string>
#include <chrono>

bool called = false;

using seconds = std::chrono::seconds;
void sleep(seconds sec)
{
    std::this_thread::sleep_for(sec);
}

void you()
{
    std::cout << "You: Eat breakfast\n";
    sleep(seconds{1});
    std::cout << "You: Work\n";
    sleep(seconds{2});
    std::cout << "You: Eat lunch\n";
    sleep(seconds{1});
    std::cout << "You: Call Bob\n";
    called = true;
}

void bob()
{
    std::cout << "Bob: Eat breakfast\n";
    sleep(seconds{1});
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
