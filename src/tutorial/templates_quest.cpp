#include "tutorial/quests.hpp"
#include "tutorial/quest.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <type_traits>
#include <memory>

namespace tutorial {

// Level 3: Templates Quest Implementation
TemplatesQuest::TemplatesQuest() 
    : Quest("Templates & Generics", "Master template programming and generic algorithms", 3) {}

void TemplatesQuest::start() {
    log("Time to master template programming! This is where C++ becomes truly powerful.");
    
    demonstrateFunctionTemplates();
    TutorialHelper::waitForEnter();
    
    demonstrateClassTemplates();
    TutorialHelper::waitForEnter();
    
    demonstrateVariadicTemplates();
    TutorialHelper::waitForEnter();
    
    demonstrateTypeTraits();
    TutorialHelper::waitForEnter();
    
    demonstrateSTLAlgorithms();
    
    if (TutorialHelper::askYesNo("Do you understand template programming and generics?")) {
        completed_ = true;
        markCompleted();
    } else {
        log("Templates are advanced! Review the examples and try again when ready.");
    }
}

bool TemplatesQuest::isCompleted() const {
    return completed_;
}

void TemplatesQuest::demonstrateFunctionTemplates() {
    TutorialHelper::printHeader("Function Templates & Generic Programming");
    
    TutorialHelper::printCode(R"(
// Basic function template
template<typename T>
T maximum(const T& a, const T& b) {
    return (a > b) ? a : b;
}

// Template with multiple parameters
template<typename T, typename U>
auto add(const T& a, const U& b) -> decltype(a + b) {
    return a + b;
}

// Template specialization for strings
template<>
std::string maximum<std::string>(const std::string& a, const std::string& b) {
    return (a.length() > b.length()) ? a : b;
}

// Generic container processor
template<typename Container, typename Func>
void processContainer(const Container& container, Func func) {
    for (const auto& element : container) {
        func(element);
    }
}
)");

    std::cout << "\nLive demonstration:\n";
    
    // Function template usage
    auto intMax = [](int a, int b) { return (a > b) ? a : b; };
    auto strMax = [](const std::string& a, const std::string& b) { 
        return (a.length() > b.length()) ? a : b; 
    };
    
    std::cout << "max(10, 5) = " << intMax(10, 5) << "\n";
    std::cout << "max(\"hello\", \"world!\") = " << strMax("hello", "world!") << "\n";
    
    std::vector<int> numbers{1, 2, 3, 4, 5};
    std::cout << "Processing vector: ";
    for (const auto& num : numbers) {
        std::cout << num * 2 << " ";
    }
    std::cout << "\n";
}

void TemplatesQuest::demonstrateClassTemplates() {
    TutorialHelper::printHeader("Class Templates & Generic Data Structures");
    
    TutorialHelper::printCode(R"(
// Basic class template
template<typename T>
class Container {
private:
    std::vector<T> data_;
    
public:
    void add(const T& item) { data_.push_back(item); }
    
    size_t size() const { return data_.size(); }
    
    T& operator[](size_t index) { return data_[index]; }
    const T& operator[](size_t index) const { return data_[index]; }
    
    // Range-based for loop support
    auto begin() { return data_.begin(); }
    auto end() { return data_.end(); }
    auto begin() const { return data_.begin(); }
    auto end() const { return data_.end(); }
};

// Template with non-type parameters
template<typename T, size_t N>
class FixedArray {
private:
    T data_[N];
    
public:
    constexpr size_t size() const { return N; }
    T& operator[](size_t index) { return data_[index]; }
    const T& operator[](size_t index) const { return data_[index]; }
};
)");

    std::cout << "\nLive demonstration:\n";
    std::cout << "Templates allow type-safe, efficient generic programming!\n";
}

void TemplatesQuest::demonstrateVariadicTemplates() {
    TutorialHelper::printHeader("Variadic Templates & Parameter Packs");
    
    TutorialHelper::printCode(R"(
// Variadic function template
template<typename T>
void print(const T& value) {
    std::cout << value << "\n";
}

template<typename T, typename... Args>
void print(const T& first, const Args&... rest) {
    std::cout << first << " ";
    print(rest...);  // Recursive call
}

// Variadic template with fold expressions (C++17)
template<typename... Args>
auto sum(Args... args) {
    return (args + ...);  // Fold expression
}
)");

    std::cout << "\nLive demonstration:\n";
    std::cout << "Variadic templates enable flexible function interfaces!\n";
}

void TemplatesQuest::demonstrateTypeTraits() {
    TutorialHelper::printHeader("Type Traits & Template Metaprogramming");
    
    TutorialHelper::printCode(R"(
#include <type_traits>

// SFINAE (Substitution Failure Is Not An Error)
template<typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type
process_integral(T value) {
    return value * 2;
}

// Concept-like template constraints (C++20 style)
template<typename T>
requires std::is_arithmetic_v<T>
T square(T value) {
    return value * value;
}
)");

    std::cout << "\nLive demonstration:\n";
    std::cout << "Type traits enable compile-time decisions!\n";
}

void TemplatesQuest::demonstrateSTLAlgorithms() {
    TutorialHelper::printHeader("STL Algorithms & Generic Programming");
    
    TutorialHelper::printCode(R"(
#include <algorithm>
#include <numeric>

std::vector<int> numbers{5, 2, 8, 1, 9, 3};

// Transform algorithm
std::vector<int> squared;
std::transform(numbers.begin(), numbers.end(), 
               std::back_inserter(squared),
               [](int x) { return x * x; });

// Count with predicate
int evenCount = std::count_if(numbers.begin(), numbers.end(),
                             [](int x) { return x % 2 == 0; });
)");

    std::cout << "\nLive demonstration:\n";
    
    std::vector<int> demo_numbers{5, 2, 8, 1, 9, 3};
    std::cout << "Original: ";
    for (int n : demo_numbers) std::cout << n << " ";
    std::cout << "\n";
    
    std::vector<int> squared;
    std::transform(demo_numbers.begin(), demo_numbers.end(), 
                   std::back_inserter(squared),
                   [](int x) { return x * x; });
    
    std::cout << "Squared:  ";
    for (int n : squared) std::cout << n << " ";
    std::cout << "\n";
    
    std::cout << "STL algorithms provide powerful generic operations!\n";
}

}  // namespace tutorial