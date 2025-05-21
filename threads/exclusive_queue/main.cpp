#include <vector>
#include "../../Threads.h"

// this code demonstrates the exclusive queue pattern where only two threads
// can pair up at a time. They do whatever they need as a pair and meet at a
// rendezvous point and release the lock before anyone else can pair up and go

// this is a game show where guys and girls get paired with each other. guys and girls arrive
// at different intervals and match up with whoever's there. if no one is available,
// they wait for someone to come. the guy then solves a math question while the girl
// solves a science question. only one  pair can go at a time to have the spotlight on
// them. whoever in the pair finishes first has to wait for the other to cross the finish line.
// only after they finish can another pair match up and do the game

// this pattern does not ensure sequential pairing but only ensures that one 'guy' gets paired
// with one 'girl' and one pair proceed at a time while others wait

// only one pair can be under the spotlight at a time
std::mutex spotlight;

// blocks thread as they wait for a pair
std::counting_semaphore<10> guyQueue{0};
std::counting_semaphore<10> girlQueue{0};

// rendezvous point at finish line
std::binary_semaphore finishLine{0};

// keeps track of how many guys/girls are waiting to be paired
int guys{};
int girls{};

void guy(char id)
{
    std::stringstream msg;
    msg << "Guy " << id << " arrived at the starting line" << std::endl;
    std::cout << msg.str();

    // take the mutex to check for matches
    spotlight.lock();
        msg.str("");
        if (girls > 0) // there is already a girl waiting
        {
            msg << "Guy " << id << " found a match" << std::endl;
            std::cout << msg.str();
            --girls; // decrement number of girls available
            guyQueue.release(); // signal one girl thread waiting for a guy to unblock
        } else // no girls are waiting to be paired yet
        {
            msg << "Guy " << id << " is waiting for a match" << std::endl;
            std::cout << msg.str();
            ++guys; // add to number of guys waiting
            spotlight.unlock(); // release mutex so other ppl can check for a match
            girlQueue.acquire(); // block to wait for a girl
        }

        // atp the guy is matched and doing the game
        msg.str("");
        msg << "Guy " << id << " is doing the math questions" << std::endl;
        std::cout << msg.str();
        sleep(2, 5); // take some time to answer questions

        msg.str("");
        msg << "Guy "<< id << " is done!" << std::endl;

        // wait for girl to finish since guy will be releasing the mutex
        finishLine.acquire();
        std::cout << msg.str();

    // only the guy releases the mutex. if the guy released to wait for a girl,
    // the girl will lock it and the guy will unlock. if the guy held it from the
    // start, then he will lock and unlock
    spotlight.unlock();
}

void girl(char id)
{
    std::stringstream msg;
    msg << "Girl " << id << " arrived at the starting line" << std::endl;
    std::cout << msg.str();

    // take mutex to check for matches
    spotlight.lock();
        msg.str("");
        if (guys > 0) // there is already a guy waiting
        {
            msg << "Girl " << id << " found a match" << std::endl;
            std::cout << msg.str();
            --guys; // decrement number of guys waiting
            girlQueue.release(); // signal the guy waiting to unblock
        } else // no guy is waiting yet
        {
            msg << "Girl " << id << " is waiting for a match" << std::endl;
            std::cout << msg.str();
            ++girls; // one more girl waiting
            spotlight.unlock(); // release mutex so others can get paired
            guyQueue.acquire(); // block to wait for a guy
        }

    // atp the girl is paired and doing the game
    msg.str("");
    msg << "Girl " << id << " is doing the science questions" << std::endl;
    std::cout << msg.str();
    sleep(1, 4); // take some time to answer questions

    msg.str("");
    msg << "Girl " << id << " is done!" << std::endl;
    std::cout << msg.str();
    finishLine.release(); // let the guy know that she is done to cross finish line
    // no releasing of mutex here since the guy will be unlocking
}

void sendGirls(std::vector<std::thread>& girls)
{
    for (int i{}; i < 10; ++i)
    {
        sleep(4, 6); // girls take longer to get ready

        // girls are A - J
        girls.emplace_back(girl, 65 + i);
    }

    for (auto& g : girls)
    {
        g.join();
    }
}

void sendGuys(std::vector<std::thread>& guys)
{
    for (int i{}; i < 10; ++i)
    {
        sleep(2, 5);

        // guys are a - j
        guys.emplace_back(guy, 97 + i);
    }

    for (auto& g : guys)
    {
        g.join();
    }
}

int main()
{
    std::vector<std::thread> guys{};
    guys.reserve(10);
    std::vector<std::thread> girls{};
    girls.reserve(10);

    // create threads to send the girls and guys in randomly
    std::thread pushGirls(sendGirls, std::ref(girls));
    std::thread pushGuys(sendGuys, std::ref(guys));

    pushGirls.join();
    pushGuys.join();
}
