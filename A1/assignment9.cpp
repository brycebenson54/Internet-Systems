#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex mtx;
condition_variable santa_cv, reindeer_cv, elves_cv;
int num_reindeer = 0, num_elves = 0;

void santa() {
    unique_lock<mutex> lock(mtx);
    while (true) {
        santa_cv.wait(lock, [] { return num_reindeer == 9 || num_elves == 3; });

        if (num_reindeer == 9) {
            cout << "Santa is helping the reindeer" << endl;
            num_reindeer = 0;
            reindeer_cv.notify_all();
        } else if (num_elves == 3) {
            cout << "Santa is helping the elves" << endl;
            num_elves = 0;
            elves_cv.notify_all();
        }


        if (num_reindeer == 0 && num_elves == 0) {
            break;
        }
    }
}

void reindeer() {
    unique_lock<mutex> lock(mtx);
    num_reindeer++;
    if (num_reindeer == 9) {
        santa_cv.notify_one();
    }
    reindeer_cv.wait(lock);
}

void elves() {
    unique_lock<mutex> lock(mtx);
    num_elves++;
    if (num_elves == 3) {
        santa_cv.notify_one();
    }
    elves_cv.wait(lock);
}

int main() {
    thread santa_thread(santa);
    thread reindeer_threads[9];
    thread elf_threads[num_elves];

    for (int i = 0; i < 9; ++i) {
        reindeer_threads[i] = thread(reindeer);
    }

    for (int i = 0; i < num_elves; ++i) {
        elf_threads[i] = thread(elves);
    }

    santa_thread.join();
    for (int i = 0; i < 9; ++i) {
        reindeer_threads[i].join();
    }
    for (int i = 0; i < num_elves; ++i) {
        elf_threads[i].join();
    }

    return 0;
}