#include "../../Threads.h"

// to solve the starvation problem, we add a turnstile where
// each time a writer wants to write, they lock the turnstile
// so any new readers have to wait. as the room clears out, the
// writer gets to write and then only the readers enter

// however, there is still a problem. if a writer is going to write
// then chances are the current data is already obsolete. hence, writers
// need to be prioritised at all cost so readers get the most updated data

std::binary_semaphore roomEmpty{1};
std::binary_semaphore turnstile{1}; // starts open
int numYounglings{};
std::mutex mutex;


void master(int id)
{
    while (true)
    {
        std::stringstream msg;
        msg << "Jedi Master " << id <<  " has something new to add to the archive" << std::endl;
        std::cout << msg.str();

        turnstile.acquire(); // locks the turnstile

        // if blocks here, no yl can enter archives
        // since turnstile is locked
        roomEmpty.acquire();

        // in this section, room is confirmed to be empty so no need
        // for a mutex or lock of any kind
        std::cout << "Jedi Master " << id << " writing to archives" << std::endl;
        sleep(2, 5);
        std::cout << "Jedi Master " << id << " is done writing" << std::endl;

        // this order here does not matter but i guess unlocking turnstile
        // before signalling that the room is empty makes more sense
        turnstile.release(); // unlock turnstile
        roomEmpty.release();

        msg.str("");
        msg << "Jedi Master " << id << " going on next mission" << std::endl;
        std::cout << msg.str();

        // shorter sleep here to show that writers are not prioritized
        // a writer could be lined up but still get overtaken by readers
        sleep(1, 3);
    }

}

void youngling(int id)
{
    while (true)
    {
        std::stringstream msg;

        msg << "Youngling " << id << " wants to enter the archive" << std::endl;
        std::cout << msg.str();

        // if a master is waiting to write, younglings block here
        turnstile.acquire(); // has to make sure turnstile is unlocked first and relock
        turnstile.release(); // unlock it again for next youngling

        mutex.lock();
            ++numYounglings;

            if (numYounglings == 1)
            {
                msg.str("");
                msg << "Youngling " << id << " is first to arrive. Waiting for room to be empty" << std::endl;
                std::cout << msg.str();
                roomEmpty.acquire();
            }
        mutex.unlock();

        msg.str("");
        msg << "Youngling " << id << " entered the archive and is reading some books" << std::endl;
        std::cout << msg.str();
        sleep(1, 2);

        msg.str("");
        msg << "Youngling " << id << " is leaving the archives" << std::endl;
        std::cout << msg.str();

        mutex.lock();
            --numYounglings;

            if (numYounglings == 0)
            {
                msg.str("");
                msg << "Youngling " << id << " is last to leave. Telling masters that room is empty" << std::endl;
                std::cout << msg.str();
                roomEmpty.release();
            }
        mutex.unlock();

        sleep(2, 5);
    }

}

void sendYounglings(threads& younglings)
{
    for (int i{1}; i <= 5; ++i)
    {
        sleep(0, 2);
        younglings.emplace_back(youngling, i);
    }

    for (auto& y : younglings)
    {
        y.join();
    }
}

void sendMasters(threads& masters)
{
    for (int i{1}; i <= 2; ++i)
    {
        sleep(2, 5);
        masters.emplace_back(master, i);
    }

    for (auto& m : masters)
    {
        m.join();
    }
}

int main()
{
    threads younglings{};
    threads masters{};

    // send younglings and masters randomly
    std::thread pushYounglings(sendYounglings, std::ref(younglings));
    std::thread pushMasters(sendMasters, std::ref(masters));    

    pushYounglings.join();
    pushMasters.join();
}
