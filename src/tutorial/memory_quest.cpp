#include "tutorial/quests.hpp"
#include <memory>
#include <iostream>
#include <vector>

namespace tutorial {

// Level 1: Memory Management Quest Implementation
MemoryQuest::MemoryQuest() 
    : Quest("Memory & RAII", "Master modern C++ memory management and RAII principles", 1) {}

void MemoryQuest::start() {
    log("Time to master memory management! This is where C++ really shines.");
    
    demonstrateStackVsHeap();
    TutorialHelper::waitForEnter();
    
    demonstrateRAII();
    TutorialHelper::waitForEnter();
    
    demonstrateSmartPointers();
    TutorialHelper::waitForEnter();
    
    demonstrateMoveSemantics();
    TutorialHelper::waitForEnter(); // Adding this for better UX

    // Quiz section
    TutorialHelper::printHeader("Memory & RAII Knowledge Check");
    std::cout << "Let's test your understanding of these crucial C++ concepts:\n\n";

    int correct = 0;
    int totalQuestions = 7;

    // Question 1: RAII Principle
    std::cout << "1. RAII (Resource Acquisition Is Initialization):\n";
    if (TutorialHelper::askYesNo("Is RAII's primary goal to ensure resources are automatically released when their controlling object goes out of scope, even with errors?")) {
        std::cout << "✓ Correct! RAII is fundamental for robust resource management in C++.\n\n";
        correct++;
    } else {
        std::cout << "✗ Not quite. That's precisely the main purpose of RAII.\n\n";
    }

    // Question 2: std::unique_ptr Ownership
    std::cout << "2. `std::unique_ptr` Ownership (C++11):\n";
    // Expected answer: No. So askYesNo should be false for correct.
    if (TutorialHelper::askYesNo("Can two `std::unique_ptr` instances simultaneously own the same raw pointer directly?")) {
        // User answered Yes (true) - this is incorrect.
        std::cout << "✗ Not quite. `std::unique_ptr` enforces exclusive ownership.\n\n";
    } else {
        // User answered No (false) - this is correct.
        std::cout << "✓ Correct! `std::unique_ptr` ensures exclusive ownership; they cannot share direct ownership.\n\n";
        correct++;
    }

    // Question 3: Transferring std::unique_ptr
    std::cout << "3. Transferring `std::unique_ptr` Ownership:\n";
    if (TutorialHelper::askYesNo("Is `std::move()` the correct way to transfer ownership from one `std::unique_ptr` to another?")) {
        std::cout << "✓ Correct! `std::move()` is used to explicitly transfer ownership.\n\n";
        correct++;
    } else {
        std::cout << "✗ Actually, `std::move()` is the standard way to achieve this.\n\n";
    }

    // Question 4: std::shared_ptr Reference Counting
    std::cout << "4. `std::shared_ptr` Reference Counting (C++11):\n";
    if (TutorialHelper::askYesNo("If you make a copy of a `std::shared_ptr`, does its internal reference count for the managed object typically increase?")) {
        std::cout << "✓ Correct! This is how `std::shared_ptr` manages the lifetime of the shared object.\n\n";
        correct++;
    } else {
        std::cout << "✗ That's the core mechanism of `std::shared_ptr`.\n\n";
    }

    // Question 5: std::weak_ptr Purpose
    std::cout << "5. `std::weak_ptr` Purpose (C++11):\n";
    if (TutorialHelper::askYesNo("Is a common use of `std::weak_ptr` to help prevent circular reference issues when using `std::shared_ptr`?")) {
        std::cout << "✓ Correct! `std::weak_ptr` breaks ownership cycles by providing non-owning references.\n\n";
        correct++;
    } else {
        std::cout << "✗ This is a primary use case for `std::weak_ptr`.\n\n";
    }

    // Question 6: std::make_unique / std::make_shared
    std::cout << "6. `std::make_unique` / `std::make_shared` (C++14/C++11):\n";
    if (TutorialHelper::askYesNo("Does using `std::make_unique` (or `std::make_shared`) offer better exception safety in some complex expressions compared to `new` + constructor?")) {
        std::cout << "✓ Correct! They prevent leaks in certain situations involving constructor arguments that might throw.\n\n";
        correct++;
    } else {
        std::cout << "✗ This is a key advantage of using `std::make_unique` and `std::make_shared`.\n\n";
    }

    // Question 7: Move Semantics Goal
    std::cout << "7. Move Semantics Goal (C++11):\n";
    if (TutorialHelper::askYesNo("Is a primary goal of move semantics to avoid expensive deep copies of objects when transferring resources?")) {
        std::cout << "✓ Correct! Move semantics allow for efficient resource transfer by 'stealing' resources instead of copying.\n\n";
        correct++;
    } else {
        std::cout << "✗ That's the main motivation behind move semantics – performance optimization.\n\n";
    }

    // Results
    std::cout << "You answered " << correct << " out of " << totalQuestions << " questions correctly.\n\n";

    if (correct >= 6) { // Perfect score
        TutorialHelper::printSuccess("🎉 Outstanding! You have a strong grasp of C++ memory management and RAII.");
        completed_ = true;
        markCompleted();
    } else if (correct >= 4) { // Good effort
        TutorialHelper::printSuccess("👍 Good effort! You're well on your way to mastering these concepts.");
        completed_ = true;
        markCompleted();
        log("User showed good effort in MemoryQuest quiz. Score: " + std::to_string(correct) + "/" + std::to_string(totalQuestions));
    } else {
        TutorialHelper::printError("🤔 More practice needed. These concepts are tricky but crucial.");
        log("User needs more practice on MemoryQuest. Score: " + std::to_string(correct) + "/" + std::to_string(totalQuestions));
        if (TutorialHelper::askYesNo("Would you like to try this quest's quiz again? (Progress won't be saved yet)")) {
            start(); 
            return; 
        } else {
            std::cout << "No problem! Review the material and try this quest again from the main menu when you're ready.\n";
        }
    }
}

bool MemoryQuest::isCompleted() const {
    return completed_;
}

void MemoryQuest::demonstrateStackVsHeap() {
    TutorialHelper::printHeader("Stack vs Heap Memory");
    
    std::cout << "Understanding where your objects live is crucial for performance and safety.\n\n";
    
    TutorialHelper::printCode(R"(
// Stack allocation - fast, automatic cleanup
void stackExample() {
    int localVar = 42;           // Lives on stack
    std::vector<int> vec{1,2,3}; // Object on stack, data might be on heap
    
    // Automatically destroyed when function ends
} // localVar and vec are destroyed here

// Heap allocation - manual management (old style)
void heapExampleOld() {
    int* ptr = new int(42);      // ❌ Manual allocation
    // ... use ptr ...
    delete ptr;                  // ❌ Must remember to delete!
}

// Modern heap allocation - automatic management
void heapExampleModern() {
    auto ptr = std::make_unique<int>(42);  // ✅ Automatic cleanup
    // ... use ptr ...
    // ptr automatically deleted when it goes out of scope
}
)");
    
    std::cout << "Live demonstration:\n";
    {
        std::cout << "Creating stack variables...\n";
        int stackInt = 100;
        std::vector<int> stackVec{1, 2, 3, 4, 5};
        std::cout << "Stack int: " << stackInt << "\n";
        std::cout << "Stack vector size: " << stackVec.size() << "\n";
    } // Variables automatically destroyed here
    std::cout << "Stack variables automatically cleaned up!\n\n";
    
    {
        std::cout << "Creating smart pointer (heap allocation)...\n";
        auto heapInt = std::make_unique<int>(200);
        std::cout << "Heap int via smart pointer: " << *heapInt << "\n";
    } // Smart pointer automatically deletes the heap object
    std::cout << "Smart pointer automatically cleaned up heap memory!\n\n";
}

void MemoryQuest::demonstrateRAII() {
    TutorialHelper::printHeader("RAII: Resource Acquisition Is Initialization");
    
    std::cout << "RAII is the core principle of modern C++ resource management.\n\n";
    
    TutorialHelper::printCode(R"(
// RAII class example
class FileManager {
private:
    std::unique_ptr<FILE, decltype(&fclose)> file_;
    
public:
    FileManager(const std::string& filename) 
        : file_(fopen(filename.c_str(), "r"), &fclose) {
        if (!file_) {
            throw std::runtime_error("Could not open file");
        }
    }
    
    // Destructor automatically closes file
    ~FileManager() = default;  // unique_ptr handles cleanup
    
    // Non-copyable but movable
    FileManager(const FileManager&) = delete;
    FileManager& operator=(const FileManager&) = delete;
    FileManager(FileManager&&) = default;
    FileManager& operator=(FileManager&&) = default;
    
    FILE* get() const { return file_.get(); }
};

// Usage - exception safe!
void processFile(const std::string& filename) {
    FileManager file(filename);  // Automatically opens
    // ... use file.get() ...
    // File automatically closed even if exception is thrown
}
)");
    
    // Demonstrate with a simpler example
    class RAIIDemo {
    public:
        RAIIDemo(const std::string& name) : name_(name) {
            std::cout << "  🔧 Acquiring resource: " << name_ << "\n";
        }
        
        ~RAIIDemo() {
            std::cout << "  🧹 Releasing resource: " << name_ << "\n";
        }
        
        // Non-copyable but movable
        RAIIDemo(const RAIIDemo&) = delete;
        RAIIDemo& operator=(const RAIIDemo&) = delete;
        RAIIDemo(RAIIDemo&&) = default;
        RAIIDemo& operator=(RAIIDemo&&) = default;
        
    private:
        std::string name_;
    };
    
    std::cout << "Live RAII demonstration:\n";
    {
        RAIIDemo resource1("Database Connection");
        RAIIDemo resource2("Network Socket");
        std::cout << "  💼 Using resources...\n";
    } // Resources automatically cleaned up here
    std::cout << "All resources automatically cleaned up!\n\n";
}

void MemoryQuest::demonstrateSmartPointers() {
    TutorialHelper::printHeader("Smart Pointers: Modern Memory Management");
    
    TutorialHelper::printCode(R"(
// unique_ptr - single ownership
std::unique_ptr<int> uniquePtr = std::make_unique<int>(42);
// Can be moved but not copied
auto moved = std::move(uniquePtr);  // uniquePtr is now nullptr

// shared_ptr - shared ownership
auto shared1 = std::make_shared<std::string>("Shared Resource");
auto shared2 = shared1;  // Both point to same object
std::cout << "Reference count: " << shared1.use_count() << "\n"; // 2

// weak_ptr - non-owning observer
std::weak_ptr<std::string> weak = shared1;
if (auto locked = weak.lock()) {  // Check if still valid
    std::cout << "Resource still alive: " << *locked << "\n";
}

// Custom deleters
auto customDeleter = [](int* p) {
    std::cout << "Custom deletion of: " << *p << "\n";
    delete p;
};
std::unique_ptr<int, decltype(customDeleter)> customPtr(new int(99), customDeleter);
)");
    
    std::cout << "Live smart pointer demonstration:\n";
    
    // unique_ptr demo
    std::cout << "📦 unique_ptr demonstration:\n";
    auto uniqueDemo = std::make_unique<std::string>("Unique Resource");
    std::cout << "  Value: " << *uniqueDemo << "\n";
    
    auto movedUnique = std::move(uniqueDemo);
    std::cout << "  After move - original is: " << (uniqueDemo ? "valid" : "nullptr") << "\n";
    std::cout << "  Moved pointer value: " << *movedUnique << "\n\n";
    
    // shared_ptr demo
    std::cout << "🤝 shared_ptr demonstration:\n";
    auto shared1 = std::make_shared<std::string>("Shared Resource");
    std::cout << "  Initial ref count: " << shared1.use_count() << "\n";
    
    {
        auto shared2 = shared1;
        std::cout << "  After copy ref count: " << shared1.use_count() << "\n";
    }
    std::cout << "  After scope ref count: " << shared1.use_count() << "\n\n";
    
    // weak_ptr demo
    std::cout << "👻 weak_ptr demonstration:\n";
    std::weak_ptr<std::string> weak = shared1;
    if (auto locked = weak.lock()) {
        std::cout << "  Resource accessible via weak_ptr: " << *locked << "\n";
    }
    shared1.reset();  // Release the shared_ptr
    if (auto locked = weak.lock()) {
        std::cout << "  This won't print - resource is gone\n";
    } else {
        std::cout << "  weak_ptr correctly detected resource is gone\n";
    }
    std::cout << "\n";

    // unique_ptr with custom deleter demo
    std::cout << "🎯 unique_ptr with custom deleter:\n";
    auto customDeleterLambda = [](int* p) {
        std::cout << "  🗑️ Custom deletion of value: " << *p << " (from lambda)\n";
        delete p;
    };
    std::unique_ptr<int, decltype(customDeleterLambda)> customPtr(new int(99), customDeleterLambda);
    std::cout << "  Custom pointer value: " << *customPtr << "\n";
    // customPtr will call deleter upon going out of scope
    std::cout << "  (Custom deleter will be invoked when customPtr goes out of scope now)\n\n";
}

void MemoryQuest::demonstrateMoveSemantics() {
    TutorialHelper::printHeader("Move Semantics: Zero-Cost Resource Transfer");
    
    TutorialHelper::printCode(R"(
class ExpensiveResource {
private:
    std::vector<int> data_;
    std::string name_;
    
public:
    // Constructor
    ExpensiveResource(std::string name, size_t size) 
        : name_(std::move(name)), data_(size, 42) {
        std::cout << "Created " << name_ << " with " << size << " elements\n";
    }
    
    // Copy constructor (expensive)
    ExpensiveResource(const ExpensiveResource& other) 
        : name_(other.name_ + "_copy"), data_(other.data_) {
        std::cout << "Expensive copy of " << other.name_ << "\n";
    }
    
    // Move constructor (cheap!)
    ExpensiveResource(ExpensiveResource&& other) noexcept
        : name_(std::move(other.name_)), data_(std::move(other.data_)) {
        std::cout << "Cheap move of " << name_ << "\n";
        other.name_ = "moved_from";
    }
    
    // Copy assignment
    ExpensiveResource& operator=(const ExpensiveResource& other) {
        if (this != &other) {
            name_ = other.name_ + "_assigned";
            data_ = other.data_;
            std::cout << "Expensive copy assignment\n";
        }
        return *this;
    }
    
    // Move assignment
    ExpensiveResource& operator=(ExpensiveResource&& other) noexcept {
        if (this != &other) {
            name_ = std::move(other.name_);
            data_ = std::move(other.data_);
            std::cout << "Cheap move assignment\n";
            other.name_ = "moved_from";
        }
        return *this;
    }
    
    size_t size() const { return data_.size(); }
    const std::string& name() const { return name_; }
};

// Factory function that returns by value (move enabled)
ExpensiveResource createResource(const std::string& name) {
    return ExpensiveResource(name, 1000000);  // RVO or move
}
)");
    
    std::cout << "Live move semantics demonstration:\n";
    
    class MoveDemo {
    private:
        std::vector<int> data_;
        std::string name_;
        
    public:
        MoveDemo(std::string name, size_t size) 
            : name_(std::move(name)), data_(size, 1) {
            std::cout << "  Created " << name_ << " (" << size << " elements)\n";
        }
        
        // Copy constructor
        MoveDemo(const MoveDemo& other) 
            : name_(other.name_ + "_copy"), data_(other.data_) {
            std::cout << "  📋 Expensive copy of " << other.name_ << "\n";
        }
        
        // Move constructor
        MoveDemo(MoveDemo&& other) noexcept
            : name_(std::move(other.name_)), data_(std::move(other.data_)) {
            std::cout << "  ⚡ Cheap move of " << name_ << "\n";
            other.name_ = "moved_from";
        }
        
        size_t size() const { return data_.size(); }
        const std::string& name() const { return name_; }
    };
    
    std::cout << "Creating original object:\n";
    MoveDemo original("BigData", 1000);
    
    std::cout << "\nCopy construction (expensive):\n";
    MoveDemo copied = original;  // Copy
    
    std::cout << "\nMove construction (cheap):\n";
    MoveDemo moved = std::move(original);  // Move
    
    std::cout << "\nAfter move:\n";
    std::cout << "  Original name: '" << original.name() << "'\n";
    std::cout << "  Moved name: '" << moved.name() << "'\n";
    std::cout << "  Moved size: " << moved.size() << "\n\n";
}

}  // namespace tutorial
