#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <random>

int NUM_PHILOSOPHERS;
std::vector<std::unique_ptr<std::mutex>> forks; //array of mutex's (is this how you write it?XD) each one is a fork
std::mutex cout_mutex; //one guy talking at a time so stuff will actually make sense

void think(int id) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100 + rand() % 900));
}

void eat(int id) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100 + rand() % 900));
}
//both think and eat is in a range of 100 - 999 ms
void philosopher(int id) {
    while (true) {
        think(id);
        std::cout << "Philosopher " << id << " thinks.\n";
        int left = id; //left fork
        int right = (id + 1) % NUM_PHILOSOPHERS; //right fork

        //HERE IS THE VERY IMPORTANT PART
        if (id % 2 == 0) { //even dudes pick up the left one first
            forks[left]->lock();
            forks[right]->lock();
        }
        else { //uneven dudes pick up the right one first
            forks[right]->lock();
            forks[left]->lock();
        } //thanks to that we won't have a situation where they all they the left fork
          //and consequently that lead to a deadlock

        {
            std::lock_guard<std::mutex> lock(cout_mutex); //one guy talks at a time
            std::cout << "Philosopher " << id << " eats.\n";
        }

        eat(id); //we eat, and when we are done

        forks[left]->unlock(); //put the forks down
        forks[right]->unlock();
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Use: " << argv[0] << " <number_of_philosophers>\n";
        return 1;
    }
    NUM_PHILOSOPHERS = std::atoi(argv[1]);
    if (NUM_PHILOSOPHERS < 2) {
        std::cerr << "Number of philosophers has to be at least 2.\n";
        return 1;
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        forks.emplace_back(std::make_unique<std::mutex>());
    }

    std::vector<std::thread> philosophers; //vector of threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosophers.emplace_back(philosopher, i); //each philosopher gets his own thread
    }

    for (auto& p : philosophers) {
        p.join(); //pohilosophers don't stop eating, so program never endsXD
    }

    return 0;
}
