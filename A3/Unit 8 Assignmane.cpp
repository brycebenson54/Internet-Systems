#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <semaphore.h>

const int MAX_EAT_COUNT = 5;

std::vector<sem_t> utensils;
std::vector<std::mutex> forks;
std::vector<int> eatCount;

void philosopher(int id) {
    int leftFork = id;
    int rightFork = (id + 1) % utensils.size();

    while (eatCount[id] < MAX_EAT_COUNT) {
        std::cout << "Philosopher " << id << " is thinking" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        sem_wait(&utensils[leftFork]);
        sem_wait(&utensils[rightFork]);
        forks[leftFork].lock();
        forks[rightFork].lock();
        std::cout << "Philosopher " << id << " is eating" << std::endl;
        forks[leftFork].unlock();
        forks[rightFork].unlock();
        sem_post(&utensils[leftFork]);
        sem_post(&utensils[rightFork]);
        eatCount[id]++;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " <number of philosophers> <number of utensils>" << std::endl;
        return 1;
    }

    int numPhilosophers = std::stoi(argv[1]);
    int numUtensils = std::stoi(argv[2]);

    if (numPhilosophers < 4 || numUtensils < 4) {
        std::cout << "Please provide at least 4 philosophers and 4 utensils." << std::endl;
        return 1;
    }

    utensils.resize(numUtensils);
    forks.resize(numUtensils);
    eatCount.resize(numPhilosophers, 0);

    for (int i = 0; i < numUtensils; ++i) {
        sem_init(&utensils[i], 0, 1);
    }

    std::vector<std::thread> philosopherThreads;
    for (int i = 0; i < numPhilosophers; ++i) {
        philosopherThreads.emplace_back(philosopher, i);
    }

    for (auto& thread : philosopherThreads) {
        thread.join();
    }

    for (int i = 0; i < numUtensils; ++i) {
        sem_destroy(&utensils[i]);
    }

    return 0;
}
