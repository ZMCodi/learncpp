#include "../../Threads.h"

// this is a more generalized problem where agents dont wait for smokers to
// make the cigs but instead just keep pushing out ingredients as they please
// but to make the output somewhat easier to follow, we add a 1 sec pause for each agent

using sem = std::binary_semaphore;

sem tobacco{0};
sem paper{0};
sem match{0};

// agent threads. each subagent waits for agentSem to be signalled
// and then provides the ingredients that they carry. In the interesting
// version of the problem, this code is not to be modified

// agent A
void not_match()
{
    while (true)
    {
        std::cout << "Agent A providing tobacco\n";
        tobacco.release();
        std::cout << "Agent A providing paper\n";
        paper.release();
        sleep(0, 0, secs{1});
    }
}

// agent B
void not_tobacco()
{
    while (true)
    {
        std::cout << "Agent B providing paper\n";
        paper.release();
        std::cout << "Agent B providing match\n";
        match.release();
        sleep(0, 0, secs{1});
    }
}

// agent C
void not_paper()
{
    while (true)
    {
        std::cout << "Agent C providing match\n";
        match.release();
        std::cout << "Agent C providing tobacco\n";
        tobacco.release();
        sleep(0, 0, secs{1});
    }
}

// the pushers now have to track how many ingredients as opposed to boolean flags

// flags for tracking resources
int isPaper{};
int isTobacco{};
int isMatch{};

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
        std::cout << "Pusher got paper\n";

        mutex.lock();
        if (isTobacco)
        {
            // if tobacco already available
            --isTobacco;
            std::cout << "Signalling match smoker\n";
            matchSem.release();
        } else if (isMatch)
        {
            // if match already available
            --isMatch;
            std::cout << "Signalling tobacco smoker\n";
            tobaccoSem.release();
        } else
        {
            // if nothing else is available (first pusher)
            std::stringstream msg;
            msg << "Paper stock: " << ++isPaper << "\n";
            std::cout << msg.str();
        }

        mutex.unlock();
    }
}

void matchPusher()
{
    while (true)
    {
        match.acquire();
        std::cout << "Pusher got match\n";

        mutex.lock();
        if (isTobacco)
        {
            --isTobacco;
            std::cout << "Signalling paper smoker\n";
            paperSem.release();
        } else if (isPaper)
        {
            --isPaper;
            std::cout << "Signalling tobacco smoker\n";
            tobaccoSem.release();
        } else
        {
            std::stringstream msg;
            msg << "Match stock: " << ++isMatch << "\n";
            std::cout << msg.str();
        }

        mutex.unlock();
    }
}

void tobaccoPusher()
{
    while (true)
    {
        tobacco.acquire();
        std::cout << "Pusher got tobacco\n";

        mutex.lock();
        if (isMatch)
        {
            --isMatch;
            std::cout << "Signalling paper smoker\n";
            paperSem.release();
        } else if (isPaper)
        {
            --isPaper;
            std::cout << "Signalling match smoker\n";
            matchSem.release();
        } else
        {
            std::stringstream msg;
            msg << "Tobacco stock: " << ++isTobacco << "\n";
            std::cout << msg.str();
        }

        mutex.unlock();
    }
}

// in this case, the smokers dont take time though they should
// but this demo is to just show how the pushers work in case
// of the agents not waiting

void match_smoker()
{
    while (true)
    {
        matchSem.acquire();
        std::cout << "Smoker with match making cigarettes\n";
    }
}

void tobacco_smoker()
{
    while (true)
    {
        tobaccoSem.acquire();
        std::cout << "Smoker with tobacco making cigarettes\n";
    }
}

void paper_smoker()
{
    while (true)
    {
        paperSem.acquire();
        std::cout << "Smoker with paper making cigarettes\n";
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
