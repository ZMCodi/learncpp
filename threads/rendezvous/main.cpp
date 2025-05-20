#include "../../Threads.h"

std::binary_semaphore aArrived{0};
std::binary_semaphore bArrived{0};

void A()
{
    while (true)
    {
        // a doing something before rendezvous
        std::cout << "a doing espionage at CIA\n";
        sleep(2, 10);

        // a is done, signal that it has arrived
        std::cout << "a has arrived at rendezvous point\n";
        aArrived.release();

        // wait for b to arrive
        bArrived.acquire();

        // share secrets with b
        std::cout << "sharing secrets\n";
        sleep(0, 0, secs{3});
    }
    
}

void B()
{
    while (true)
    {
        // b doing something before rendezvous
        std::cout << "b doing espionage at FBI\n";
        sleep(2, 10);

        // b is done, signal that it has arrived
        std::cout << "b has arrived at rendezvous point\n";
        bArrived.release();

        // wait for a to arrive
        aArrived.acquire();

        // sharing secrets with a
        sleep(0, 0, secs{3});
    }

}

int main()
{
    std::thread a(A);
    std::thread b(B);

    a.join();
    b.join();
}
