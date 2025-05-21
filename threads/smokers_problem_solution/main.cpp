#include "../../Threads.h"

// to solve this deadlock, we need pushers that synchronize with each other
// and determine which smoker to signal based on which resources are available

using sem = std::binary_semaphore;

sem tobacco{0};
sem paper{0};
sem match{0};
sem agentSem{1};

// agent threads. each subagent waits for agentSem to be signalled
// and then provides the ingredients that they carry. In the interesting
// version of the problem, this code is not to be modified

// agent A
void not_match()
{
    while (true)
    {
        agentSem.acquire();
        std::cout << "Agent A providing tobacco" << std::endl;
        tobacco.release();
        std::cout << "Agent A providing paper" << std::endl;
        paper.release();
        sleep(1, 3); // remove this to see no deadlock happens
    }
}

// agent B
void not_tobacco()
{
    while (true)
    {
        agentSem.acquire();
        std::cout << "Agent B providing paper" << std::endl;
        paper.release();
        std::cout << "Agent B providing match" << std::endl;
        match.release();
        sleep(1, 3); // remove this to see no deadlock happens
    }
}

// agent C
void not_paper()
{
    while (true)
    {
        agentSem.acquire();
        std::cout << "Agent C providing match" << std::endl;
        match.release();
        std::cout << "Agent C providing tobacco" << std::endl;
        tobacco.release();
        sleep(1, 3); // remove this to see no deadlock happens
    }
}

// the pushers track what resources are available and decide to signal the appropriate smoker

// flags for tracking resources
bool isPaper{false};
bool isTobacco{false};
bool isMatch{false};

// semaphores to signal the smokers
sem paperSem{0};
sem tobaccoSem{0};
sem matchSem{0};

std::mutex mutex;

// pushers only get one resource each and coordinate with each other using the flags
void paperPusher()
{
    while (true)
    {
        paper.acquire();
        std::cout << "Pusher got paper" << std::endl;

        mutex.lock();
        if (isTobacco)
        {
            isTobacco = false;
            std::cout << "Signalling match smoker" << std::endl;
            matchSem.release();
        } else if (isMatch)
        {
            isMatch = false;
            std::cout << "Signalling tobacco smoker" << std::endl;
            tobaccoSem.release();
        } else
        {
            isPaper = true;
        }

        mutex.unlock();
    }
}

void matchPusher()
{
    while (true)
    {
        match.acquire();
        std::cout << "Pusher got match" << std::endl;

        mutex.lock();
        if (isTobacco)
        {
            isTobacco = false;
            std::cout << "Signalling paper smoker" << std::endl;
            paperSem.release();
        } else if (isPaper)
        {
            isPaper = false;
            std::cout << "Signalling tobacco smoker" << std::endl;
            tobaccoSem.release();
        } else
        {
            isMatch = true;
        }

        mutex.unlock();
    }
}

void tobaccoPusher()
{
    while (true)
    {
        tobacco.acquire();
        std::cout << "Pusher got tobacco" << std::endl;

        mutex.lock();
        if (isMatch)
        {
            isMatch = false;
            std::cout << "Signalling paper smoker" << std::endl;
            paperSem.release();
        } else if (isPaper)
        {
            isPaper = false;
            std::cout << "Signalling match smoker" << std::endl;
            matchSem.release();
        } else
        {
            isTobacco = true;
        }

        mutex.unlock();
    }
}

// each smoker just waits for the signal from their pushers

void match_smoker()
{
    while (true)
    {
        matchSem.acquire();
        std::cout << "Smoker with match making cigarettes" << std::endl;
        agentSem.release();
    }
}

void tobacco_smoker()
{
    while (true)
    {
        tobaccoSem.acquire();
        std::cout << "Smoker with tobacco making cigarettes" << std::endl;
        agentSem.release();
    }
}

void paper_smoker()
{
    while (true)
    {
        paperSem.acquire();
        std::cout << "Smoker with paper making cigarettes" << std::endl;
        agentSem.release();
    }
}

int main()
{
    threads t{};
    t.emplace_back(not_match);
    t.emplace_back(not_paper);
    t.emplace_back(not_tobacco);
    t.emplace_back(paper_smoker);
    t.emplace_back(match_smoker);
    t.emplace_back(tobacco_smoker);
    t.emplace_back(paperPusher);
    t.emplace_back(tobaccoPusher);
    t.emplace_back(matchPusher);

    for (auto& thread : t)
    {
        thread.join();
    }

}
