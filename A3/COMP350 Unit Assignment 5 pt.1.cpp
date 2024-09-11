#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <algorithm>

void calculateSum(const std::vector<int>& numbers, int start, int end, int& result) {
    for (int i = start; i <= end; ++i) {
        result += numbers[i];
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <number_of_threads> <input_file_name>" << std::endl;
        return 1;
    }

    int numThreads = std::stoi(argv[1]);
    std::string fileName = argv[2];

    std::ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open input file." << std::endl;
        return 1;
    }

    int numElements;
    inputFile >> numElements;
    std::vector<int> numbers(numElements);

    for (int i = 0; i < numElements; ++i) {
        inputFile >> numbers[i];
    }

    inputFile.close();

    int elementsPerThread = numElements / numThreads;
    std::vector<std::thread> threads;
    std::vector<int> partialSums(numThreads, 0);

    for (int i = 0; i < numThreads; ++i) {
        int start = i * elementsPerThread;
        int end = (i == numThreads - 1) ? numElements - 1 : start + elementsPerThread - 1;
        threads.emplace_back(calculateSum, std::ref(numbers), start, end, std::ref(partialSums[i]));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    int totalSum = std::accumulate(partialSums.begin(), partialSums.end(), 0);
    std::cout << "Total Sum: " << totalSum << std::endl;
    std::ofstream outputFile("output.txt");
    
    if (outputFile.is_open()) {
        outputFile << "Total Sum: " << totalSum << std::endl;
        outputFile.close();
    } else {
        std::cerr << "Error: Unable to create/open output.txt file." << std::endl;
        return 1;
    }

    return 0;
}
