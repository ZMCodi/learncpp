#include "../../Threads.h"
#include <deque>
#include <vector>

// classic producer consumer problem
// producer adds stuff into buffer
// consumer takes stuff out
// only one thread can access the buffer at one time
// producer can only put into buffer if there is space
// consumer can only take from buffer if there are items
// no good analogy here but i think the problem is easy enough to understand

constexpr int BUFFER_SIZE{5};
std::counting_semaphore<BUFFER_SIZE> items{0};
std::counting_semaphore<BUFFER_SIZE> spaces{BUFFER_SIZE};
std::mutex mutex{};

std::deque<int> buffer{};

void producer(int id)
{
    while (true)
    {
        std::stringstream msg;
        msg << "Producer " << id << " producing...\n";
        std::cout << msg.str();
        sleep(2, 5); // simulate waiting to produce

        int product{Random::get(1, 100)};
        msg.str("");
        msg << "Producer " << id << " produced " << product << '\n';

        // wait for space to put stuff
        spaces.acquire(); // if full, blocks here
        {
            std::lock_guard<std::mutex> lock(mutex);
            buffer.push_back(product); // 'produce' and push into queue

            std::cout << "Producer " << id << " added " << product << " to buffer\n";
            items.release(); // let consumers know an item was added
        }
    }
}

void consumer(int id)
{
    while (true)
    {
        std::stringstream msg;
        msg << "Consumer " << id << " trying to consume\n";
        std::cout << msg.str();

        int product;
        // wait for items to take out
        items.acquire(); // if empty, blocks here
        {
            std::lock_guard<std::mutex> lock(mutex);
            product = buffer.front();
            buffer.pop_front(); // std::queue doesn't return the element on pop lol
            std::cout << "Consumer " << id << " retrieved " << product << " from buffer\n";
            spaces.release(); // let producers know there is an empty space
        }

        msg.str("");
        msg << "Consumer " << id << " is processing " << product << '\n';
        std::cout << msg.str();
        sleep(1, 3); // processing is quicker in this case
    }
}

void monitor()
{
    while (true)
    {
        sleep(0, 0, secs{1});
        std::stringstream msg;
        msg << "[ ";
        for (int prod : buffer)
        {
            msg << prod << ' ';
        }
        msg << "]\n";

        std::cout << msg.str();
    }
}

int main()
{
    std::vector<std::thread> producers{};
    for (int i{1}; i <= 5; ++i)
    {
        producers.emplace_back(producer, i);
    }

    // there are less consumers than producers
    // so the buffer has a chance to fill up
    std::vector<std::thread> consumers{};
    for (int i{1}; i <= 3; ++i)
    {
        consumers.emplace_back(consumer, i);
    }

    std::thread Monitor(monitor);

    for (auto& p : producers)
    {
        p.join();
    }

    for (auto& c : consumers)
    {
        c.join();
    }

    Monitor.join();
}
