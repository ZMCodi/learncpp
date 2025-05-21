#include "../../Threads.h"

// to solve the priority problem, we use the lightswitch twice.
// the writers uses the LS pattern on a semaphore which ensures
// no readers enter until all writers (even those who come later)
// leave. the readers also use the LS pattern to ensure no writers
// come in until all of them leave but this is the same as the previous ones.

std::binary_semaphore noReaders{1};
std::binary_semaphore noWriters{1}; // starts open
int numYounglings{};
int numMasters{};

// we need two mutexes here for reader and writer since they are independent
// and have their own variables to take care of
std::mutex readerMutex;
std::mutex writerMutex;


void master(int id)
{
    while (true)
    {
        std::stringstream msg;
        msg << "Jedi Master " << id <<  " has something new to add to the archive\n";
        std::cout << msg.str();

        writerMutex.lock();
            ++numMasters; // add to number of masters writing

            // lightswitch here
            if (numMasters == 1) // first master to write
            {
                msg.str("");
                msg << "Jedi Master " << id << " is first to arrive. Preventing younglings from entering\n";
                std::cout << msg.str();
                noReaders.acquire(); // blocks any younglings trying to enter
            }
        writerMutex.unlock();

        // this waits for all younglings to leave
        // and any other masters coming in will block here
        noWriters.acquire();

        // in this section, room is confirmed to be empty so no need
        // for a mutex or lock of any kind
        std::cout << "Jedi Master " << id << " writing to archives\n";
        sleep(2, 5);
        std::cout << "Jedi Master " << id << " is done writing\n";

        noWriters.release(); // let other writers in now
        writerMutex.lock();
            --numMasters;

            if (numMasters == 0) // last master to leave
            {
                msg.str("");
                msg << "Jedi Master " << id << " is last to leave. Letting the younglings back in\n";
                std::cout << msg.str();
                noReaders.release(); // let younglings back in
            }
        writerMutex.unlock();

        msg.str("");
        msg << "Jedi Master " << id << " going on next mission\n";
        std::cout << msg.str();

        // big range here so that sometimes writers might come in close succession
        // showcasing the priority where they can 'cut the queue' of readers
        // while also still allowing gaps where readers can come in
        sleep(3, 10);
    }

}

void youngling(int id)
{
    while (true)
    {
        std::stringstream msg;

        msg << "Youngling " << id << " wants to enter the archive\n";
        std::cout << msg.str();

        // wait for masters to let younglings back in
        // or for the youngling who just entered to signal
        noReaders.acquire(); 
        readerMutex.lock(); // we still need this to guard if one reader is entering while one is exiting
            ++numYounglings;

            if (numYounglings == 1)
            {
                msg.str("");
                msg << "Youngling " << id << " is first to arrive. Waiting for room to be empty\n";
                std::cout << msg.str();
                noWriters.acquire(); // block masters from coming in
            }
        readerMutex.unlock();
        noReaders.release(); // let the next youngling in

        msg.str("");
        msg << "Youngling " << id << " entered the archive and is reading some books\n";
        std::cout << msg.str();
        sleep(1, 2);

        msg.str("");
        msg << "Youngling " << id << " is leaving the archives\n";
        std::cout << msg.str();

        readerMutex.lock();
            --numYounglings;

            if (numYounglings == 0)
            {
                msg.str("");
                msg << "Youngling " << id << " is last to leave. Telling masters that room is empty\n";
                std::cout << msg.str();
                noWriters.release();
            }
        readerMutex.unlock();

        sleep(2, 5);
    }
}

void sendYounglings(threads& younglings)
{
    for (int i{1}; i <= 7; ++i)
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
    for (int i{1}; i <= 3; ++i)
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
