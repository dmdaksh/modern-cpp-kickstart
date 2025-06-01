#include "tutorial/quests.hpp"
#include "tutorial/quest.hpp"
#include <iostream>
#include <vector>
#include <string>

namespace tutorial {

// Level 0: Basics Quest Implementation
BasicsQuest::BasicsQuest() 
    : Quest("C++ Basics", "Learn fundamental C++ syntax, types, and control structures", 0) {}

void BasicsQuest::start() {
    log("Welcome to C++ Basics! Let's start with the fundamentals.");
    
    demonstrateTypes();
    TutorialHelper::waitForEnter();
    
    demonstrateControlFlow();
    TutorialHelper::waitForEnter();
    
    demonstrateFunctions();
    
    if (TutorialHelper::askYesNo("Do you understand the basics of C++ syntax?")) {
        completed_ = true;
        markCompleted();
    } else {
        log("Take your time to review the concepts. You can restart this quest anytime!");
    }
}

bool BasicsQuest::isCompleted() const {
    return completed_;
}

void BasicsQuest::demonstrateTypes() {
    TutorialHelper::printHeader("Modern C++ Types");
    
    std::cout << "C++ has evolved to include many powerful type features:\n\n";
    
    TutorialHelper::printCode(R"(
// Fundamental types
int age = 25;                    // 32-bit integer
double pi = 3.14159;            // Double precision floating point
bool isLearning = true;         // Boolean
char initial = 'A';             // Single character
std::string name = "Developer"; // String (from <string>)

// Auto type deduction (C++11)
auto x = 42;        // x is int
auto y = 3.14;      // y is double
auto z = "Hello";   // z is const char*

// Modern initialization (C++11)
int numbers{10};           // Uniform initialization
std::vector<int> vec{1, 2, 3, 4, 5}; // Container initialization
)");
    
    // Demonstrate actual usage
    std::cout << "Live demonstration:\n";
    auto demo_int = 42;
    auto demo_string = std::string("Modern C++");
    std::vector<int> demo_vec{1, 2, 3};
    
    std::cout << "Auto-deduced int: " << demo_int << "\n";
    std::cout << "String: " << demo_string << "\n";
    std::cout << "Vector contents: ";
    for (const auto& num : demo_vec) {
        std::cout << num << " ";
    }
    std::cout << "\n\n";
}

void BasicsQuest::demonstrateControlFlow() {
    TutorialHelper::printHeader("Control Flow Structures");
    
    TutorialHelper::printCode(R"(
// Range-based for loop (C++11) - Preferred in modern C++
std::vector<std::string> languages{"C++", "Python", "JavaScript"};
for (const auto& lang : languages) {
    std::cout << "Learning: " << lang << "\n";
}

// If with initializer (C++17)
if (auto result = calculateSomething(); result > 0) {
    std::cout << "Positive result: " << result << "\n";
}

// Switch with fallthrough attributes (C++17)
enum class Color { Red, Green, Blue };
auto color = Color::Red;

switch (color) {
    case Color::Red:
        std::cout << "Red color\n";
        break;
    case Color::Green:
        std::cout << "Green color\n";
        break;
    case Color::Blue:
        std::cout << "Blue color\n";
        break;
}
)");
    
    std::cout << "Live demonstration:\n";
    std::vector<std::string> demo_languages{"C++", "Rust", "Go"};
    for (const auto& lang : demo_languages) {
        std::cout << "🔥 Learning: " << lang << "\n";
    }
    std::cout << "\n";
}

void BasicsQuest::demonstrateFunctions() {
    TutorialHelper::printHeader("Modern Function Features");
    
    TutorialHelper::printCode(R"(
// Function with default parameters
int add(int a, int b = 0) {
    return a + b;
}

// Lambda functions (C++11)
auto multiply = [](int a, int b) -> int {
    return a * b;
};

// Generic lambda (C++14)
auto print = [](const auto& value) {
    std::cout << value << "\n";
};

// Constexpr functions (C++11/14)
constexpr int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

// Using functions
int result1 = add(5, 3);        // 8
int result2 = add(5);           // 5 (uses default parameter)
int result3 = multiply(4, 6);   // 24
constexpr int fact5 = factorial(5); // Computed at compile time!
)");
    
    // Live demonstration
    std::cout << "Live demonstration:\n";
    
    auto addDemo = [](int a, int b = 10) { return a + b; };
    auto printValue = [](const auto& value) {
        std::cout << "Value: " << value << "\n";
    };
    
    std::cout << "Lambda add(5, 3): " << addDemo(5, 3) << "\n";
    std::cout << "Lambda add(5): " << addDemo(5) << "\n";
    
    printValue(42);
    printValue("Hello World");
    printValue(3.14159);
    
    std::cout << "\n";
}

}  // namespace tutorial
