#include <iostream>
#include <thread>

void countNumbers(int threadID) {
    for (int i = 0; i <= 10; ++i) {
        std::cout << "Thread " << threadID << ": Count " << i << std::endl;
    }
}

int main() {
    std::thread thread1(countNumbers, 1);
    std::thread thread2(countNumbers, 2);
    thread1.join();
    thread2.join();
    return 0;
}
