#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>
#include <random>

const int NUM_PHILOSOPHERS = 5;
std::mutex forks[NUM_PHILOSOPHERS];
std::mutex cout_mutex;

void think(int id) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100 + rand() % 900));
}

void eat(int id) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100 + rand() % 900));
}

void philosopher(int id) {
    while (true) {
        think(id);
        std::cout << "Filozof " << id << " mysli.\n";
        int left = id;
        int right = (id + 1) % NUM_PHILOSOPHERS;

        if (id % 2 == 0) {
            forks[left].lock();
            forks[right].lock();
        }
        else {
            forks[right].lock();
            forks[left].lock();
        }

        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Filozof " << id << " je.\n";
        }

        eat(id);

        forks[left].unlock();
        forks[right].unlock();
    }
}

int main() {
    std::vector<std::thread> philosophers;
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosophers.emplace_back(philosopher, i);
    }

    for (auto& p : philosophers) {
        p.join();
    }

    return 0;
}
