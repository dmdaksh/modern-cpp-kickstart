#include "tutorial/quests.hpp"
#include "tutorial/quest.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <string>

namespace tutorial {

// Level 4: STL Quest Implementation
STLQuest::STLQuest() 
    : Quest("STL Containers & Algorithms", "Master the Standard Template Library containers and algorithms", 4) {}

void STLQuest::start() {
    log("Time to explore the Standard Template Library! The power of C++ lies in its rich ecosystem.");
    
    demonstrateSequenceContainers();
    TutorialHelper::waitForEnter();
    
    demonstrateAssociativeContainers();
    TutorialHelper::waitForEnter();
    
    demonstrateContainerAdaptors();
    TutorialHelper::waitForEnter();
    
    demonstrateIterators();
    TutorialHelper::waitForEnter();
    
    demonstrateAlgorithms();
    
    if (TutorialHelper::askYesNo("Do you understand STL containers and algorithms?")) {
        completed_ = true;
        markCompleted();
    } else {
        log("STL is vast! Review the examples and explore the documentation.");
    }
}

bool STLQuest::isCompleted() const {
    return completed_;
}

void STLQuest::demonstrateSequenceContainers() {
    TutorialHelper::printHeader("Sequence Containers: Linear Collections");
    
    TutorialHelper::printCode(R"(
// std::vector - Dynamic array (most commonly used)
std::vector<int> vec{1, 2, 3, 4, 5};
vec.push_back(6);                    // O(1) amortized
vec.insert(vec.begin() + 2, 10);     // O(n) - shifts elements

// std::deque - Double-ended queue
std::deque<std::string> deq{"b", "c", "d"};
deq.push_front("a");                 // O(1) - efficient at both ends
deq.push_back("e");                  // O(1)

// std::list - Doubly-linked list
std::list<double> lst{1.1, 2.2, 3.3};
lst.push_front(0.5);                 // O(1)
)");

    std::cout << "\nLive demonstration:\n";
    
    std::vector<int> demo_vec{1, 2, 3};
    std::cout << "Vector: ";
    for (int n : demo_vec) std::cout << n << " ";
    demo_vec.push_back(4);
    std::cout << "-> after push_back(4): ";
    for (int n : demo_vec) std::cout << n << " ";
    std::cout << "\n";
    
    std::cout << "Choose the right container for your access patterns!\n";
}

void STLQuest::demonstrateAssociativeContainers() {
    TutorialHelper::printHeader("Associative Containers: Key-Value Collections");
    
    TutorialHelper::printCode(R"(
// std::map - Ordered key-value pairs (Red-Black Tree)
std::map<std::string, int> ages;
ages["Alice"] = 30;
ages["Bob"] = 25;

// std::unordered_map - Hash table (faster average case)
std::unordered_map<int, std::string> employees;
employees[101] = "John Doe";
employees[102] = "Jane Smith";

// std::set - Ordered unique elements
std::set<int> unique_numbers{3, 1, 4, 1, 5, 9, 2, 6};
// Result: {1, 2, 3, 4, 5, 6, 9} - sorted and unique
)");

    std::cout << "\nLive demonstration:\n";
    
    std::map<std::string, int> demo_ages;
    demo_ages["Alice"] = 30;
    demo_ages["Bob"] = 25;
    
    std::cout << "Ages map: ";
    for (const auto& [name, age] : demo_ages) {
        std::cout << name << ":" << age << " ";
    }
    std::cout << "\n";
    
    std::cout << "Associative containers provide efficient lookup!\n";
}

void STLQuest::demonstrateContainerAdaptors() {
    TutorialHelper::printHeader("Container Adaptors: Specialized Interfaces");
    
    TutorialHelper::printCode(R"(
// std::stack - LIFO (Last In, First Out)
std::stack<int> stack;
stack.push(1);
stack.push(2);
stack.push(3);
// stack.top() == 3

// std::queue - FIFO (First In, First Out)
std::queue<std::string> queue;
queue.push("first");
queue.push("second");
// queue.front() == "first"

// std::priority_queue - Max heap by default
std::priority_queue<int> pq;
pq.push(3);
pq.push(1);
pq.push(4);
// pq.top() == 4 (largest element)
)");

    std::cout << "\nLive demonstration:\n";
    
    std::stack<int> demo_stack;
    demo_stack.push(1);
    demo_stack.push(2);
    demo_stack.push(3);
    
    std::cout << "Stack operations (LIFO): ";
    while (!demo_stack.empty()) {
        std::cout << demo_stack.top() << " ";
        demo_stack.pop();
    }
    std::cout << "\n";
    
    std::cout << "Container adaptors provide intuitive interfaces!\n";
}

void STLQuest::demonstrateIterators() {
    TutorialHelper::printHeader("Iterators: The Bridge Between Containers and Algorithms");
    
    TutorialHelper::printCode(R"(
std::vector<int> vec{1, 2, 3, 4, 5};

// Basic iterator usage
auto it = vec.begin();
std::cout << *it << "\n";        // Dereference: 1
++it;                            // Advance

// Range-based iteration
for (auto it = vec.begin(); it != vec.end(); ++it) {
    std::cout << *it << " ";
}

// Reverse iterators
for (auto rit = vec.rbegin(); rit != vec.rend(); ++rit) {
    std::cout << *rit << " ";    // Prints: 5 4 3 2 1
}
)");

    std::cout << "\nLive demonstration:\n";
    
    std::vector<int> demo_vec{10, 20, 30, 40, 50};
    
    std::cout << "Forward iteration: ";
    for (auto it = demo_vec.begin(); it != demo_vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    
    std::cout << "Iterators provide a unified interface!\n";
}

void STLQuest::demonstrateAlgorithms() {
    TutorialHelper::printHeader("STL Algorithms: Powerful Generic Operations");
    
    TutorialHelper::printCode(R"(
#include <algorithm>
#include <numeric>

std::vector<int> numbers{5, 2, 8, 1, 9, 3, 7, 4, 6};

// Sorting and searching
std::sort(numbers.begin(), numbers.end());
auto it = std::find(numbers.begin(), numbers.end(), 5);

// Transformation algorithms
std::vector<int> squared(numbers.size());
std::transform(numbers.begin(), numbers.end(), squared.begin(),
               [](int x) { return x * x; });

// Numeric algorithms
int sum = std::accumulate(numbers.begin(), numbers.end(), 0);

// Count algorithms
int evenCount = std::count_if(numbers.begin(), numbers.end(),
                             [](int x) { return x % 2 == 0; });
)");

    std::cout << "\nLive demonstration:\n";
    
    std::vector<int> demo_numbers{5, 2, 8, 1, 9, 3};
    
    std::cout << "Original: ";
    for (int n : demo_numbers) std::cout << n << " ";
    std::cout << "\n";
    
    std::sort(demo_numbers.begin(), demo_numbers.end());
    std::cout << "Sorted:   ";
    for (int n : demo_numbers) std::cout << n << " ";
    std::cout << "\n";
    
    int sum = std::accumulate(demo_numbers.begin(), demo_numbers.end(), 0);
    std::cout << "Sum: " << sum << "\n";
    
    std::cout << "STL algorithms provide efficient implementations!\n";
}

}  // namespace tutorial