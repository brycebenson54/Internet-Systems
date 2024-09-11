#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>

const int BUFFER_SIZE = 100; 
std::vector<int> buffer;
std::mutex mtx;
std::condition_variable bufferEmpty, bufferFull;

void producer(int id) {
    for (int i = 1; i <= 10; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        bufferFull.wait(lock, []{ return buffer.size() < BUFFER_SIZE; });
        buffer.push_back(i);
        std::cout << "Producer " << id << " produced item " << i << std::endl;
        lock.unlock();
        bufferEmpty.notify_one();
    }
}

void consumer(int id) {
    for (int i = 0; i < 10; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        bufferEmpty.wait(lock, []{ return !buffer.empty(); });
        int item = buffer.back();
        buffer.pop_back();
        std::cout << "Consumer " << id << " consumed item " << item << std::endl;
        lock.unlock();
        bufferFull.notify_one();
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <num_producers> <num_consumers>" << std::endl;
        return 1;
    }

    int numProducers = std::stoi(argv[1]);
    int numConsumers = std::stoi(argv[2]);

    std::vector<std::thread> producerThreads, consumerThreads;

    for (int i = 1; i <= numProducers; ++i) {
        producerThreads.emplace_back(producer, i);
    }

    for (int i = 1; i <= numConsumers; ++i) {
        consumerThreads.emplace_back(consumer, i);
    }

    for (auto& t : producerThreads) {
        t.join();
    }

    for (auto& t : consumerThreads) {
        t.join();
    }

    return 0;
}
