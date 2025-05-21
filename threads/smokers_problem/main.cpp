#include "../../Threads.h"

// this code illustrates the smoker problem where there are threads that
// require resources (smokers) and OS code that provide these resources (agents)
// the problem is how to appropriately allocate the resources to not cause a deadlock

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
    agentSem.acquire();
    std::cout << "Agent A providing tobacco" << std::endl;
    tobacco.release();
    std::cout << "Agent A providing paper" << std::endl;
    paper.release();
}

// agent B
void not_tobacco()
{
    agentSem.acquire();
    std::cout << "Agent B providing paper" << std::endl;
    paper.release();
    std::cout << "Agent B providing match" << std::endl;
    match.release();
}

// agent C
void not_paper()
{
    agentSem.acquire();
    std::cout << "Agent C providing match" << std::endl;
    match.release();
    std::cout << "Agent C providing tobacco" << std::endl;
    tobacco.release();
}

// each smoker has one ingredient and waits for the other two from the agent
// to create their cigarette. this is a naive implementation that results in a deadlock

void match_smoker()
{
    std::cout << "Smoker with match getting paper" << std::endl;
    paper.acquire();
    std::cout << "Smoker with match getting tobacco" << std::endl;
    tobacco.acquire();
    agentSem.release();
}

void tobacco_smoker()
{
    std::cout << "Smoker with tobacco getting match" << std::endl;
    match.acquire();
    std::cout << "Smoker with tobacco getting paper" << std::endl;
    paper.acquire();
    agentSem.release();
}

void paper_smoker()
{
    std::cout << "Smoker with paper getting tobacco" << std::endl;
    tobacco.acquire();
    std::cout << "Smoker with paper getting match" << std::endl;
    match.acquire();
    agentSem.release();
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

    for (auto& thread : t)
    {
        thread.join();
    }

}
