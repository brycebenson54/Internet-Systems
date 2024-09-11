#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <semaphore.h>

std::vector<int> buffer;
sem_t empty, full;
std::mutex mtx;

void producer(int id, int num_items, int buffer_size) {
    for (int i = 0; i < num_items; ++i) {
        sem_wait(&empty);
        std::unique_lock<std::mutex> lock(mtx);
        if (buffer.size() < buffer_size) {
            buffer.push_back(i);
            std::cout << "Producer " << id << " produced item: " << i << std::endl;
        }
        lock.unlock();
        sem_post(&full);
    }
}

void consumer(int id, int num_items) {
    for (int i = 0; i < num_items; ++i) {
        sem_wait(&full);
        std::unique_lock<std::mutex> lock(mtx);
        if (!buffer.empty()) {
            int item = buffer.back();
            buffer.pop_back();
            std::cout << "Consumer " << id << " consumed item: " << item << std::endl;
        }
        lock.unlock();
        sem_post(&empty);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <num_producers> <num_consumers> <buffer_size>" << std::endl;
        return 1;
    }

    int num_producers = std::stoi(argv[1]);
    int num_consumers = std::stoi(argv[2]);
    int buffer_size = std::stoi(argv[3]);

    sem_init(&empty, 0, buffer_size);
    sem_init(&full, 0, 0);

    std::vector<std::thread> threads;

    for (int i = 0; i < num_producers; ++i) {
        threads.emplace_back(producer, i, 10, buffer_size);
    }

    for (int i = 0; i < num_consumers; ++i) {
        threads.emplace_back(consumer, i, 10);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    sem_destroy(&empty);
    sem_destroy(&full);

    std::cout << "Program completed successfully." << std::endl;

    return 0;
}
