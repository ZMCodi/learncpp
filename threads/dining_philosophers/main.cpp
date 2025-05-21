#include "../../Threads.h"

// this is the classic problem in concurrency where 5 philosophers sit on a table
// with only 5 forks. at a given point, a philosopher can think, or if they are done
// thinking, they can pick up the fork to their left and right and then start eating

// the deadlock comes when each philosopher has one fork each, causing nobody to be
// able to eat and waiting for the person beside them to put down the fork (which never happens)

// run this code and you'll see the turn of events that causes the deadlock. sometimes its
// short but it can also get quite long

using sem = std::binary_semaphore;

// 5 forks on the table
sem forks[5]{
    sem(1), sem(1), sem(1), sem(1), sem(1)
};

sem fourEaten{4};

void get_forks(size_t i)
{
    // get left and right forks
    std::stringstream msg;
    msg << "Philosopher " << i << " picked up left fork (" << i << ")\n";
    forks[i].acquire();
    std::cout << msg.str();

    msg.str("");
    msg << "Philosopher " << i << " picked up right fork (" << ((i + 1) % 5) << ")\n";
    forks[(i + 1) % 5].acquire();
    std::cout << msg.str();
}

void put_forks(size_t i)
{
    // put left and right forks
    std::stringstream msg;
    msg << "Philosopher " << i << " put down left fork (" << i << ")\n";
    forks[i].release();
    std::cout << msg.str();

    msg.str("");
    msg << "Philosopher " << i << " put down right fork (" << ((i + 1) % 5) << ")\n";
    forks[(i + 1) % 5].release();
    std::cout << msg.str();
}

void philosopher(size_t id)
{
    while (true)
    {
        // think
        std::stringstream msg;
        msg << "Philosopher " << id << " thinking...\n";
        std::cout << msg.str();
        // sleep(2, 5); // this makes achieving deadlock way longer

        // eat
        get_forks(id);
        msg.str("");
        msg << "Philosopher " << id << " eating...\n";
        std::cout << msg.str();
        // sleep(2, 5);
        put_forks(id);
    }
}

int main()
{
    // add 5 philosophers
    threads philosophers{};
    for (size_t i{}; i < 5; ++i)
    {
        philosophers.emplace_back(philosopher, i);
    }

    for (auto& p : philosophers)
    {
        p.join();
    }
}
