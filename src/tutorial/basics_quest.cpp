#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "tutorial/quest.hpp"
#include "tutorial/quests.hpp"

namespace tutorial {

// Helper functions for demonstration - defined outside class to match printCode examples
int add(int a, int b = 0) {
    return a + b;
}

constexpr int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

int calculateSomething() {
    return 42;
}

// Level 0: Basics Quest Implementation
BasicsQuest::BasicsQuest()
    : Quest("C++ Basics", "Learn fundamental C++ syntax, types, and control structures", 0) {}

void BasicsQuest::start() {
    TutorialHelper::printHeader("Welcome to C++ Basics Quest!");
    log("Let's explore the fundamental building blocks of modern C++.");
    log("We'll cover types, control flow, and functions with hands-on examples.");

    demonstrateTypes();
    TutorialHelper::waitForEnter();

    demonstrateControlFlow();
    TutorialHelper::waitForEnter();

    demonstrateFunctions();
    TutorialHelper::waitForEnter();

    // Quiz section
    TutorialHelper::printHeader("Quick Knowledge Check");
    std::cout << "Let's test your understanding with a few questions:\n\n";

    int correct = 0;
    int totalQuestions = 7; // Updated total number of questions

    // Question 1: auto type deduction
    std::cout << "1. Regarding `auto` type deduction in C++ (e.g., `auto x = 10;`):\n";
    if (TutorialHelper::askYesNo("Does `auto` primarily let the compiler deduce the variable's type?")) {
        std::cout << "✓ Correct! `auto` is a powerful feature for type inference, making code cleaner.\n\n";
        correct++;
    } else {
        std::cout << "✗ Not quite. `auto` indeed lets the compiler deduce the type from the initializer.\n\n";
    }

    // Question 2: Range-based for loops
    std::cout << "2. Concerning range-based for loops (e.g., `for (int i : my_vector)`):\n";
    if (TutorialHelper::askYesNo("Is a key advantage that they simplify iteration and help prevent common errors like off-by-one?")) {
        std::cout << "✓ Excellent! Range-based for loops enhance readability and safety.\n\n";
        correct++;
    } else {
        std::cout << "✗ Actually, that's a primary benefit of range-based for loops.\n\n";
    }

    // Question 3: Uniform Initialization (C++11)
    TutorialHelper::printCode("int x{5};\nstd::vector<int> v{1,2,3};");
    std::cout << "3. Uniform Initialization (C++11) using curly braces `{}` (as shown above):\n";
    if (TutorialHelper::askYesNo("Does this initialization style help prevent narrowing conversions (e.g., `int x{7.5};` would be a warning/error)?")) {
        std::cout << "✓ Correct! Uniform initialization is stricter about type conversions, preventing potential data loss.\n\n";
        correct++;
    } else {
        std::cout << "✗ Not quite. This is a key safety feature of uniform initialization.\n\n";
    }

    // Question 4: If with Initializer (C++17)
    std::cout << "4. Consider 'if with initializer' (e.g., `if (auto val = getValue(); val > 10) {...}`):\n";
    if (TutorialHelper::askYesNo("Is a primary benefit that the initialized variable's scope (e.g., `val`) is limited to the if/else block?")) {
        std::cout << "✓ Correct! This enhances encapsulation and reduces variable scope, leading to cleaner code.\n\n";
        correct++;
    } else {
        std::cout << "✗ That's one of the main advantages, promoting better resource management and readability.\n\n";
    }

    // Question 5: Scoped Enums (C++11)
    std::cout << "5. With C++11 scoped enums (e.g., `enum class MyEnum { ValA, ValB };`):\n";
    if (TutorialHelper::askYesNo("Do you need to qualify enum values with the enum's name (e.g., `MyEnum::ValA`)?")) {
        std::cout << "✓ Correct! Scoped enums prevent naming conflicts and improve type safety.\n\n";
        correct++;
    } else {
        std::cout << "✗ Not quite. Scoped enums require qualification (e.g., `MyEnum::ValA`), unlike unscoped enums.\n\n";
    }

    // Question 6: Constexpr Functions (C++11)
    std::cout << "6. Regarding `constexpr` functions in C++11:\n";
    if (TutorialHelper::askYesNo("Can a `constexpr` function, if given constant inputs, be evaluated at compile-time?")) {
        std::cout << "✓ Correct! This allows for compile-time computation, potentially improving runtime performance.\n\n";
        correct++;
    } else {
        std::cout << "✗ That's the core idea behind `constexpr` functions – shifting computation to compile time where possible.\n\n";
    }

    // Question 7: Generic Lambdas (C++14)
    TutorialHelper::printCode("auto add = [](auto a, auto b) { return a + b; };");
    std::cout << "7. The generic lambda `add` shown above (using `auto` for parameters, C++14 feature):\n";
    if (TutorialHelper::askYesNo("Can this lambda be used to add two integers AND concatenate two `std::string` objects?")) {
        std::cout << "✓ Correct! Generic lambdas adapt to different types that support the operations within them (like `+`).\n\n";
        correct++;
    } else {
        std::cout << "✗ Actually, it can! That's the power of generic lambdas.\n\n";
    }

    // Results
    std::cout << "You answered " << correct << " out of " << totalQuestions << " questions correctly.\n\n";

    if (correct >= 6) { // Perfect score threshold adjusted
        TutorialHelper::printSuccess("🎉 Perfect score! You've truly mastered these C++ basics.");
        completed_ = true;
        markCompleted();
    } else if (correct >= 4) { // Good effort threshold adjusted
        TutorialHelper::printSuccess("👍 Good effort! You have a solid understanding.");
        completed_ = true; // Mark as completed for good effort
        markCompleted();
        log("User showed good effort in BasicsQuest quiz.");
    } else {
        TutorialHelper::printError("🤔 Keep practicing! Review the examples and explanations.");
        log("User needs more practice on BasicsQuest. Score: " + std::to_string(correct) + "/" + std::to_string(totalQuestions));
        if (TutorialHelper::askYesNo("Would you like to try the quiz again now? (Your progress on the quest won't be saved yet)")) {
            // Reset correct answers and restart quiz part.
            // This is a simplified approach; a more robust way might involve a loop or separate function.
            start(); // This will restart the whole quest, including demos. For a quiz-only retry, more refactoring is needed.
                     // For now, restarting the quest is an acceptable simplification for this context.
            return; // Prevent further execution in this call
        } else {
             std::cout << "No worries! You can restart this quest from the main menu anytime.\n";
        }
    }
}

bool BasicsQuest::isCompleted() const {
    return completed_;
}

void BasicsQuest::demonstrateTypes() {
    TutorialHelper::printHeader("Modern C++ Types & Variables");

    std::cout << "🔹 C++ offers powerful type features for safe and expressive code:\n\n";

    TutorialHelper::printCode(R"(
// Fundamental types - the building blocks
int age = 25;                    // 32-bit signed integer
double pi = 3.14159;            // Double precision floating point
bool isLearning = true;         // Boolean (true/false)
char initial = 'A';             // Single character
std::string name = "Developer"; // String class (from <string>)

// Auto type deduction (C++11) - let compiler figure out types
auto x = 42;        // x is deduced as int
auto y = 3.14;      // y is deduced as double
auto z = "Hello";   // z is deduced as const char*

// Modern initialization (C++11) - uniform brace syntax
int numbers{10};                      // Direct initialization
std::vector<int> vec{1, 2, 3, 4, 5}; // Container initialization
)");

    std::cout << "📋 Live demonstration:\n";
    std::cout << std::string(50, '-') << "\n";

    // Fundamental types
    int age = 25;
    double pi = 3.14159;
    bool isLearning = true;
    char initial = 'A';
    std::string name = "Developer";

    // Auto type deduction (C++11)
    auto x = 42;
    auto y = 3.14;
    auto z = "Hello";

    // Modern initialization (C++11)
    int numbers{10};
    std::vector<int> vec{1, 2, 3, 4, 5};

    std::cout << "Fundamental types in action:\n";
    std::cout << "  📊 age (int): " << age << "\n";
    std::cout << "  📐 pi (double): " << std::fixed << std::setprecision(5) << pi << "\n";
    std::cout << "  ✅ isLearning (bool): " << (isLearning ? "true" : "false") << "\n";
    std::cout << "  🔤 initial (char): '" << initial << "'\n";
    std::cout << "  📝 name (string): \"" << name << "\"\n\n";

    std::cout << "Auto type deduction magic:\n";
    std::cout << "  🤖 auto x = 42 → " << x << " (compiler deduced: int)\n";
    std::cout << "  🤖 auto y = 3.14 → " << y << " (compiler deduced: double)\n";
    std::cout << "  🤖 auto z = \"Hello\" → \"" << z << "\" (compiler deduced: const char*)\n\n";

    std::cout << "Modern initialization examples:\n";
    std::cout << "  📦 numbers{10}: " << numbers << "\n";
    std::cout << "  📋 vec{1,2,3,4,5}: [";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i < vec.size() - 1)
            std::cout << ", ";
    }
    std::cout << "]\n\n";
}

void BasicsQuest::demonstrateControlFlow() {
    TutorialHelper::printHeader("Control Flow Structures");

    std::cout << "🔹 Modern C++ provides elegant ways to control program flow:\n\n";

    TutorialHelper::printCode(R"(
// Range-based for loop (C++11) - cleaner iteration
std::vector<std::string> languages{"C++", "Python", "JavaScript"};
for (const auto& lang : languages) {
    std::cout << "Learning: " << lang << "\n";
}

// If with initializer (C++17) - declare and test in one line
if (auto result = calculateSomething(); result > 0) {
    std::cout << "Positive result: " << result << "\n";
}

// Scoped enums (C++11) - type-safe enumerations
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

    std::cout << "📋 Live demonstration:\n";
    std::cout << std::string(50, '-') << "\n";

    // Range-based for loop (C++11)
    std::vector<std::string> languages{"C++", "Python", "JavaScript"};
    std::cout << "🔄 Range-based for loop in action:\n";
    for (const auto& lang : languages) {
        std::cout << "  📚 Learning: " << lang << "\n";
    }
    std::cout << "\n";

    // If with initializer (C++17)
    std::cout << "⚡ If with initializer (C++17):\n";
    if (auto result = calculateSomething(); result > 0) {
        std::cout << "  ✅ Positive result: " << result << "\n";
    }
    std::cout << "\n";

    // Scoped enums (C++11)
    enum class Color { Red, Green, Blue };
    auto color = Color::Red;

    std::cout << "🎨 Scoped enum switch statement:\n";
    switch (color) {
        case Color::Red:
            std::cout << "  🔴 Red color detected\n";
            break;
        case Color::Green:
            std::cout << "  🟢 Green color detected\n";
            break;
        case Color::Blue:
            std::cout << "  🔵 Blue color detected\n";
            break;
    }
    std::cout << "\n";
}

void BasicsQuest::demonstrateFunctions() {
    TutorialHelper::printHeader("Modern Function Features");

    std::cout << "🔹 Functions are first-class citizens in modern C++:\n\n";

    TutorialHelper::printCode(R"(
// Function with default parameters
int add(int a, int b = 0) {
    return a + b;
}

// Lambda functions (C++11) - anonymous functions
auto multiply = [](int a, int b) -> int {
    return a * b;
};

// Generic lambda (C++14) - works with any printable type
auto print = [](const auto& value) {
    std::cout << "Value: " << value << "\n";
};

// Constexpr functions (C++11) - computed at compile time
constexpr int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

// Using the functions
int result1 = add(5, 3);        // 8 - both parameters provided
int result2 = add(5);           // 5 - default parameter used
int result3 = multiply(4, 6);   // 24 - lambda function call
constexpr int fact5 = factorial(5); // 120 - computed at compile time!
)");

    std::cout << "📋 Live demonstration:\n";
    std::cout << std::string(50, '-') << "\n";

    // Lambda functions (C++11)
    auto multiply = [](int a, int b) -> int { return a * b; };

    // Generic lambda (C++14)
    auto print = [](const auto& value) { std::cout << "  📤 Value: " << value << "\n"; };

    // Using the functions
    int result1 = add(5, 3);             // Uses the global function
    int result2 = add(5);                // Uses default parameter
    int result3 = multiply(4, 6);        // Uses lambda
    constexpr int fact5 = factorial(5);  // Uses constexpr function

    std::cout << "🧮 Function call results:\n";
    std::cout << "  ➕ add(5, 3) = " << result1 << " (both parameters)\n";
    std::cout << "  ➕ add(5) = " << result2 << " (using default parameter b=0)\n";
    std::cout << "  ✖️  multiply(4, 6) = " << result3 << " (lambda function)\n";
    std::cout << "  🏭 factorial(5) = " << fact5 << " (computed at compile time!)\n\n";

    std::cout << "🎯 Generic lambda examples (works with any type):\n";
    print(42);
    print("Hello, World!");
    print(3.14159);
    print(true);
    std::cout << "\n";
}

}  // namespace tutorial