#include "../../Threads.h"

// reader writer problem. at any point in time, any number
// of readers can read but if a writer wants to write/update a value, 
// the room must be empty so no obsolete values get read

// jedi younglings go to the archive to read on history of the
// jedi while every once in a while, a jedi master comes in to
// update the archives with their newest findings. the master
// only updates when the room is empty and no one can enter
// when a master is updating

// the demo highlights the lightswitch pattern, where the first
// thread to enter the 'room' will 'turn the switch on' while the
// last thread to leave 'turns it off'

// the problem with this implementation is that with sufficiently
// many readers, writers get starved since the room is never empty
// as readers keep coming in, hence writers never get to enter.
// change number of younglings to 10 and over time, you will see
// the jedi masters having to wait very long before getting their turn

std::binary_semaphore roomEmpty{1};
int numYounglings{};
std::mutex mutex;


void master(int id)
{
    while (true)
    {
        std::stringstream msg;
        msg << "Jedi Master " << id <<  " has something new to add to the archive" << std::endl;
        std::cout << msg.str();

        roomEmpty.acquire(); // wait for room to be empty before entering

        // in this section, room is confirmed to be empty so no need
        // for a mutex or lock of any kind
        std::cout << "Jedi Master " << id << " writing to archives" << std::endl;
        sleep(2, 5);
        std::cout << "Jedi Master " << id << " is done writing" << std::endl;

        roomEmpty.release(); // let all threads know room is empty again

        msg.str("");
        msg << "Jedi Master " << id << " going on next mission" << std::endl;
        std::cout << msg.str();
        sleep(5, 10); // gather more intel to add to archives
    }

}

void youngling(int id)
{
    while (true)
    {
        std::stringstream msg;

        msg << "Youngling " << id << " wants to enter the archive" << std::endl;
        std::cout << msg.str();

        mutex.lock();
            ++numYounglings; // increment number of yl in the archives

            if (numYounglings == 1) // first to enter
            {
                // has to wait for room to be empty and signal it isn't anymore
                // while it waits here, everyone else blocks at mutex
                msg.str("");
                msg << "Youngling " << id << " is first to arrive. Waiting for room to be empty" << std::endl;
                std::cout << msg.str();
                roomEmpty.acquire();
            }

        mutex.unlock();

        msg.str("");
        msg << "Youngling " << id << " entered the archive and is reading some books" << std::endl;
        std::cout << msg.str();
        sleep(1, 2); // reading only takes a short time

        msg.str("");
        msg << "Youngling " << id << " is leaving the archives" << std::endl;
        std::cout << msg.str();

        mutex.lock();
            --numYounglings; // decrement number of yl in the archives

            if (numYounglings == 0) // if last to leave
            {
                // signals that the room is now empty for any
                // masters to come in and update archives
                msg.str("");
                msg << "Youngling " << id << " is last to leave. Telling masters that room is empty" << std::endl;
                std::cout << msg.str();
                roomEmpty.release();
            }
        mutex.unlock();

        sleep(2, 5); // go do some other stuff before coming back
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
