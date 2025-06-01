#include "tutorial/quests.hpp"
#include "tutorial/quest.hpp"
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <atomic>
#include <chrono>
#include <vector>
#include <numeric>  // for std::iota and std::accumulate
#include <algorithm>

namespace tutorial {

// Level 5: Concurrency Quest Implementation
ConcurrencyQuest::ConcurrencyQuest() 
    : Quest("Concurrency & Parallel Programming", "Master multithreading, synchronization, and parallel algorithms", 5) {}

void ConcurrencyQuest::start() {
    log("Time to enter the world of concurrent programming! Handle multiple tasks simultaneously.");
    
    demonstrateBasicThreads();
    TutorialHelper::waitForEnter();
    
    demonstrateSynchronization();
    TutorialHelper::waitForEnter();
    
    demonstrateAsyncProgramming();
    TutorialHelper::waitForEnter();
    
    demonstrateAtomicOperations();
    TutorialHelper::waitForEnter();
    
    demonstrateParallelAlgorithms();
    
    if (TutorialHelper::askYesNo("Do you understand concurrency and parallel programming?")) {
        completed_ = true;
        markCompleted();
    } else {
        log("Concurrency is complex! Practice with small examples and study race conditions.");
    }
}

bool ConcurrencyQuest::isCompleted() const {
    return completed_;
}

void ConcurrencyQuest::demonstrateBasicThreads() {
    TutorialHelper::printHeader("Basic Threading: Parallel Execution");
    
    TutorialHelper::printCode(R"(
#include <thread>
#include <chrono>

// Simple thread function
void worker(int id) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Worker " << id << " completed\n";
}

// Creating and managing threads
void demonstrateThreads() {
    // Method 1: Function pointer
    std::thread t1(worker, 1);
    
    // Method 2: Lambda
    std::thread t2([](){ 
        std::cout << "Lambda thread executed\n"; 
    });
    
    // Wait for threads to complete
    t1.join();  // Block until t1 finishes
    t2.join();
    
    // Hardware concurrency
    unsigned int cores = std::thread::hardware_concurrency();
    std::cout << "Available CPU cores: " << cores << "\n";
}
)");

    std::cout << "\nLive demonstration:\n";
    
    std::cout << "Creating threads for parallel execution...\n";
    
    auto task1 = []() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "Task 1 completed\n";
    };
    
    auto task2 = []() {
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        std::cout << "Task 2 completed\n";
    };
    
    std::thread t1(task1);
    std::thread t2(task2);
    
    std::cout << "Waiting for threads to complete...\n";
    t1.join();
    t2.join();
    
    std::cout << "Hardware concurrency: " << std::thread::hardware_concurrency() << " cores\n";
    std::cout << "Threads enable true parallel execution!\n";
}

void ConcurrencyQuest::demonstrateSynchronization() {
    TutorialHelper::printHeader("Synchronization: Protecting Shared Resources");
    
    TutorialHelper::printCode(R"(
#include <mutex>

// Basic mutex for mutual exclusion
std::mutex mtx;
int shared_counter = 0;

void incrementCounter() {
    std::lock_guard<std::mutex> lock(mtx);  // RAII lock
    ++shared_counter;  // Critical section
    // Lock automatically released when guard goes out of scope
}

// Condition variable for thread communication
std::condition_variable cv;
std::mutex cv_mtx;
bool ready = false;

void producer() {
    std::lock_guard<std::mutex> lock(cv_mtx);
    ready = true;
    cv.notify_one();  // Wake up waiting thread
}

void consumer() {
    std::unique_lock<std::mutex> lock(cv_mtx);
    cv.wait(lock, []{ return ready; });  // Wait until ready is true
    std::cout << "Consumer notified!\n";
}
)");

    std::cout << "\nLive demonstration:\n";
    
    std::cout << "Demonstrating thread synchronization...\n";
    
    std::mutex demo_mtx;
    int demo_counter = 0;
    
    auto increment_task = [&demo_mtx, &demo_counter](int iterations) {
        for (int i = 0; i < iterations; ++i) {
            std::lock_guard<std::mutex> lock(demo_mtx);
            ++demo_counter;
        }
    };
    
    std::vector<std::thread> threads;
    for (int i = 0; i < 3; ++i) {
        threads.emplace_back(increment_task, 100);
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    std::cout << "Final counter value: " << demo_counter << " (should be 300)\n";
    std::cout << "Synchronization prevents race conditions!\n";
}

void ConcurrencyQuest::demonstrateAsyncProgramming() {
    TutorialHelper::printHeader("Async Programming: Futures and Promises");
    
    TutorialHelper::printCode(R"(
#include <future>

// std::async for easy asynchronous execution
auto calculate = [](int x, int y) -> int {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    return x * y + 42;
};

// Asynchronous execution
std::future<int> result = std::async(std::launch::async, calculate, 6, 7);
// Do other work while calculation runs...
int value = result.get();  // Block until result is ready

// std::promise and std::future for manual control
std::promise<std::string> promise;
std::future<std::string> future = promise.get_future();

std::thread producer([&promise]() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    promise.set_value("Hello from async thread!");
});

std::string message = future.get();  // Block until promise is fulfilled
producer.join();
)");

    std::cout << "\nLive demonstration:\n";
    
    std::cout << "Starting asynchronous calculations...\n";
    
    auto long_calculation = [](int n) -> int {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        int result = 1;
        for (int i = 1; i <= n; ++i) {
            result *= i;
        }
        return result;
    };
    
    auto future1 = std::async(std::launch::async, long_calculation, 5);
    auto future2 = std::async(std::launch::async, long_calculation, 6);
    
    std::cout << "Calculations running in parallel...\n";
    
    std::cout << "5! = " << future1.get() << "\n";
    std::cout << "6! = " << future2.get() << "\n";
    
    std::cout << "Async programming enables responsive applications!\n";
}

void ConcurrencyQuest::demonstrateAtomicOperations() {
    TutorialHelper::printHeader("Atomic Operations: Lock-Free Programming");
    
    TutorialHelper::printCode(R"(
#include <atomic>

// Atomic types for lock-free operations
std::atomic<int> atomic_counter{0};
std::atomic<bool> flag{false};

// Basic atomic operations
void atomic_increment() {
    atomic_counter++;              // Atomic increment
    atomic_counter.fetch_add(5);   // Atomic add and return old value
    int old_value = atomic_counter.exchange(100);  // Atomic swap
}

// Compare and swap (CAS) - fundamental lock-free operation
bool try_increment_if_less_than(int threshold) {
    int current = atomic_counter.load();
    while (current < threshold) {
        if (atomic_counter.compare_exchange_weak(current, current + 1)) {
            return true;  // Successfully incremented
        }
        // current now contains the actual value, retry
    }
    return false;  // Counter was >= threshold
}
)");

    std::cout << "\nLive demonstration:\n";
    
    std::cout << "Demonstrating atomic operations...\n";
    
    std::atomic<int> demo_atomic{0};
    
    auto atomic_worker = [&demo_atomic](int iterations) {
        for (int i = 0; i < iterations; ++i) {
            demo_atomic.fetch_add(1);
        }
    };
    
    std::vector<std::thread> atomic_threads;
    for (int i = 0; i < 4; ++i) {
        atomic_threads.emplace_back(atomic_worker, 250);
    }
    
    for (auto& t : atomic_threads) {
        t.join();
    }
    
    std::cout << "Atomic counter result: " << demo_atomic.load() << " (should be 1000)\n";
    std::cout << "Atomic operations enable efficient lock-free programming!\n";
}

void ConcurrencyQuest::demonstrateParallelAlgorithms() {
    TutorialHelper::printHeader("Parallel Algorithms: STL Meets Concurrency");
    
    TutorialHelper::printCode(R"(
#include <algorithm>
#include <numeric>

std::vector<int> large_data(1000000);
std::iota(large_data.begin(), large_data.end(), 1);  // Fill with 1,2,3...

// Sequential execution (traditional)
std::sort(large_data.begin(), large_data.end());

// Manual parallelism with std::thread
template<typename Iterator, typename Func>
void parallel_for_each(Iterator first, Iterator last, Func func) {
    auto length = std::distance(first, last);
    if (length < 1000) {
        std::for_each(first, last, func);  // Sequential for small ranges
        return;
    }
    
    auto num_threads = std::thread::hardware_concurrency();
    auto chunk_size = length / num_threads;
    
    std::vector<std::thread> threads;
    auto chunk_start = first;
    
    for (size_t i = 0; i < num_threads - 1; ++i) {
        auto chunk_end = chunk_start;
        std::advance(chunk_end, chunk_size);
        
        threads.emplace_back([chunk_start, chunk_end, func]() {
            std::for_each(chunk_start, chunk_end, func);
        });
        
        chunk_start = chunk_end;
    }
    
    // Handle remaining elements in main thread
    std::for_each(chunk_start, last, func);
    
    for (auto& t : threads) {
        t.join();
    }
}
)");

    std::cout << "\nLive demonstration:\n";
    
    std::cout << "Comparing sequential vs parallel processing...\n";
    
    std::vector<int> demo_data(100000);
    std::iota(demo_data.begin(), demo_data.end(), 1);
    
    auto start = std::chrono::high_resolution_clock::now();
    auto sum_seq = std::accumulate(demo_data.begin(), demo_data.end(), 0LL);
    auto end = std::chrono::high_resolution_clock::now();
    auto seq_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Sequential sum: " << sum_seq 
              << " (time: " << seq_time.count() << " μs)\n";
    
    std::cout << "Available CPU cores: " << std::thread::hardware_concurrency() << "\n";
    std::cout << "Parallel algorithms can dramatically improve performance!\n";
}

}  // namespace tutorial