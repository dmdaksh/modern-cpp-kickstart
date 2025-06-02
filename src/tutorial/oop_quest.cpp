#include "tutorial/quests.hpp"
#include <iostream>
#include <memory>
#include <vector>

namespace tutorial {

// Level 2: Object-Oriented Programming Quest Implementation
OOPQuest::OOPQuest() 
    : Quest("Object-Oriented Programming", "Master classes, inheritance, and polymorphism", 2) {}

void OOPQuest::start() {
    log("Time to explore the power of object-oriented programming in modern C++!");
    
    demonstrateClasses();
    TutorialHelper::waitForEnter();
    
    demonstrateInheritance();
    TutorialHelper::waitForEnter();
    
    demonstratePolymorphism();
    TutorialHelper::waitForEnter();
    
    demonstrateRuleOfFive();
    TutorialHelper::waitForEnter(); // Added for better flow before quiz

    // Quiz section
    TutorialHelper::printHeader("OOP Concepts & Rule of Five Check");
    std::cout << "Let's test your grasp of these important C++ OOP features:\n\n";

    int correct = 0;
    int totalQuestions = 7;

    // Question 1: Access Specifiers
    std::cout << "1. Access Specifiers:\n";
    // Expected: No. So askYesNo should be false for correct.
    if (TutorialHelper::askYesNo("If a class member is declared `private`, can it be directly accessed by functions outside the class?")) {
        // User answered Yes (true) - this is incorrect.
        std::cout << "✗ Not quite. `private` members are only accessible within the class itself.\n\n";
    } else {
        // User answered No (false) - this is correct.
        std::cout << "✓ Correct! `private` members enforce encapsulation and are not accessible from outside.\n\n";
        correct++;
    }

    // Question 2: const-Correctness
    std::cout << "2. `const`-Correctness:\n";
    if (TutorialHelper::askYesNo("Should a class member function be marked `const` if it does not modify any of the object's data members (excluding mutable members)?")) {
        std::cout << "✓ Correct! This is a key aspect of `const`-correctness, allowing the function to be called on `const` objects.\n\n";
        correct++;
    } else {
        std::cout << "✗ That's generally the best practice for `const`-correctness.\n\n";
    }

    // Question 3: Pure Virtual Functions
    std::cout << "3. Pure Virtual Functions:\n";
    if (TutorialHelper::askYesNo("If a class contains at least one pure virtual function (e.g., `virtual void draw() = 0;`), does this make the class an abstract class?")) {
        std::cout << "✓ Correct! Abstract classes with pure virtual functions cannot be instantiated directly and must be implemented by derived classes.\n\n";
        correct++;
    } else {
        std::cout << "✗ That's the definition of an abstract class in C++.\n\n";
    }

    // Question 4: Virtual Destructors
    std::cout << "4. Virtual Destructors:\n";
    if (TutorialHelper::askYesNo("Is it important for a base class to have a `virtual` destructor if objects of derived classes will be deleted through a base class pointer?")) {
        std::cout << "✓ Correct! This ensures that the correct derived class destructor is called, preventing resource leaks.\n\n";
        correct++;
    } else {
        std::cout << "✗ This is crucial for preventing undefined behavior and resource leaks in polymorphic hierarchies.\n\n";
    }

    // Question 5: override Keyword (C++11)
    std::cout << "5. `override` Keyword (C++11):\n";
    if (TutorialHelper::askYesNo("Does using `override` on a derived class's virtual function help the compiler check if it's actually overriding a base class function?")) {
        std::cout << "✓ Correct! `override` helps catch errors like mismatched function signatures during compilation.\n\n";
        correct++;
    } else {
        std::cout << "✗ That's a primary benefit of using the `override` specifier.\n\n";
    }

    // Question 6: Rule of Five
    std::cout << "6. Rule of Five:\n";
    if (TutorialHelper::askYesNo("If a class manually manages a resource (e.g., raw pointer) and you write a custom destructor, do you often need to also implement copy/move constructors and assignment operators?")) {
        std::cout << "✓ Correct! This is the essence of the Rule of Three/Five to ensure proper resource management and prevent issues like double frees or shallow copies.\n\n";
        correct++;
    } else {
        std::cout << "✗ This is a fundamental guideline for classes managing resources directly.\n\n";
    }
    
    // Question 7: final Specifier (C++11 Classes)
    std::cout << "7. `final` Specifier on Classes (C++11):\n";
    // Expected: No. So askYesNo should be false for correct.
    if (TutorialHelper::askYesNo("If a class is declared as `class MyClass final { ... };`, can another class inherit from `MyClass`?")) {
        // User answered Yes (true) - this is incorrect.
        std::cout << "✗ Not quite. `final` prevents further inheritance from that class.\n\n";
    } else {
        // User answered No (false) - this is correct.
        std::cout << "✓ Correct! The `final` specifier prohibits derivation from the class.\n\n";
        correct++;
    }

    // Results
    std::cout << "You answered " << correct << " out of " << totalQuestions << " questions correctly.\n\n";

    if (correct >= 6) { // Perfect score
        TutorialHelper::printSuccess("🎉 Excellent! Your understanding of C++ OOP principles is strong.");
        completed_ = true;
        markCompleted();
    } else if (correct >= 4) { // Good effort
        TutorialHelper::printSuccess("👍 Good work! You've got a good handle on many OOP concepts.");
        completed_ = true;
        markCompleted();
        log("User showed good effort in OOPQuest quiz. Score: " + std::to_string(correct) + "/" + std::to_string(totalQuestions));
    } else {
        TutorialHelper::printError("🤔 Keep studying! OOP is a cornerstone of C++, and mastery comes with practice.");
        log("User needs more practice on OOPQuest. Score: " + std::to_string(correct) + "/" + std::to_string(totalQuestions));
        if (TutorialHelper::askYesNo("Would you like to try this quest's quiz again? (Progress won't be saved yet)")) {
            start(); 
            return; 
        } else {
            std::cout << "No problem! You can review the OOP concepts and restart this quest anytime from the main menu.\n";
        }
    }
}

bool OOPQuest::isCompleted() const {
    return completed_;
}

void OOPQuest::demonstrateClasses() {
    TutorialHelper::printHeader("Modern C++ Classes");
    
    TutorialHelper::printCode(R"(
// Modern class with all best practices
class BankAccount {
private:
    std::string owner_;
    double balance_;
    mutable std::mutex mutex_;  // mutable for const member functions
    
public:
    // Constructor with member initializer list
    BankAccount(std::string owner, double initialBalance = 0.0)
        : owner_(std::move(owner)), balance_(initialBalance) {
        if (balance_ < 0) {
            throw std::invalid_argument("Initial balance cannot be negative");
        }
    }
    
    // Const member functions for read-only operations
    const std::string& getOwner() const { return owner_; }
    
    double getBalance() const {
        std::lock_guard<std::mutex> lock(mutex_);  // Thread-safe
        return balance_;
    }
    
    // Non-const member functions for modifications
    void deposit(double amount) {
        if (amount <= 0) {
            throw std::invalid_argument("Deposit amount must be positive");
        }
        std::lock_guard<std::mutex> lock(mutex_);
        balance_ += amount;
    }
    
    bool withdraw(double amount) {
        if (amount <= 0) {
            throw std::invalid_argument("Withdrawal amount must be positive");
        }
        std::lock_guard<std::mutex> lock(mutex_);
        if (balance_ >= amount) {
            balance_ -= amount;
            return true;
        }
        return false;
    }
    
    // Static member function
    static bool isValidAccountNumber(const std::string& accountNum) {
        return accountNum.length() >= 8 && std::all_of(accountNum.begin(), 
            accountNum.end(), ::isdigit);
    }
};
)");
    
    std::cout << "Live class demonstration:\n";
    
    class SimpleAccount {
    private:
        std::string owner_;
        double balance_;
        
    public:
        SimpleAccount(std::string owner, double balance = 0.0)
            : owner_(std::move(owner)), balance_(balance) {
            std::cout << "  💳 Created account for " << owner_ << " with $" << balance_ << "\n";
        }
        
        const std::string& getOwner() const { return owner_; }
        double getBalance() const { return balance_; }
        
        void deposit(double amount) {
            balance_ += amount;
            std::cout << "  💰 Deposited $" << amount << ". New balance: $" << balance_ << "\n";
        }
        
        bool withdraw(double amount) {
            if (balance_ >= amount) {
                balance_ -= amount;
                std::cout << "  💸 Withdrew $" << amount << ". New balance: $" << balance_ << "\n";
                return true;
            }
            std::cout << "  ❌ Insufficient funds for $" << amount << " withdrawal\n";
            return false;
        }
    };
    
    SimpleAccount account("Alice", 100.0);
    account.deposit(50.0);
    account.withdraw(30.0);
    account.withdraw(150.0);  // Should fail
    std::cout << "  Final balance: $" << account.getBalance() << "\n\n";
}

void OOPQuest::demonstrateInheritance() {
    TutorialHelper::printHeader("Inheritance and Virtual Functions");
    
    TutorialHelper::printCode(R"(
// Base class
class Vehicle {
protected:
    std::string make_;
    std::string model_;
    int year_;
    
public:
    Vehicle(std::string make, std::string model, int year)
        : make_(std::move(make)), model_(std::move(model)), year_(year) {}
    
    // Virtual destructor - ESSENTIAL for proper cleanup
    virtual ~Vehicle() = default;
    
    // Pure virtual function - makes this an abstract class
    virtual void start() = 0;
    
    // Virtual function with default implementation
    virtual void honk() const {
        std::cout << "Generic vehicle honk!\n";
    }
    
    // Non-virtual function
    void displayInfo() const {
        std::cout << year_ << " " << make_ << " " << model_ << "\n";
    }
    
    // Protected member for derived classes
protected:
    virtual void engineSound() const = 0;
};

// Derived class
class Car : public Vehicle {
private:
    int doors_;
    
public:
    Car(std::string make, std::string model, int year, int doors)
        : Vehicle(std::move(make), std::move(model), year), doors_(doors) {}
    
    // Override virtual functions
    void start() override {
        std::cout << "Car engine starting: ";
        engineSound();
    }
    
    void honk() const override {
        std::cout << "Beep beep! 🚗\n";
    }
    
protected:
    void engineSound() const override {
        std::cout << "Vroom vroom!\n";
    }
    
public:
    int getDoors() const { return doors_; }
};

class Motorcycle : public Vehicle {
public:
    Motorcycle(std::string make, std::string model, int year)
        : Vehicle(std::move(make), std::move(model), year) {}
    
    void start() override {
        std::cout << "Motorcycle engine starting: ";
        engineSound();
    }
    
    void honk() const override {
        std::cout << "Beep! 🏍️\n";
    }
    
protected:
    void engineSound() const override {
        std::cout << "Roaaaaar!\n";
    }
};
)");
    
    std::cout << "Live inheritance demonstration:\n";
    
    class Animal {
    public:
        Animal(std::string name) : name_(std::move(name)) {
            std::cout << "  🐾 Animal " << name_ << " created\n";
        }
        
        virtual ~Animal() = default;
        
        virtual void makeSound() const = 0;
        virtual void move() const {
            std::cout << "  " << name_ << " moves around\n";
        }
        
        const std::string& getName() const { return name_; }
        
    protected:
        std::string name_;
    };
    
    class Dog : public Animal {
    public:
        Dog(std::string name) : Animal(std::move(name)) {}
        
        void makeSound() const override {
            std::cout << "  🐕 " << name_ << " says: Woof! Woof!\n";
        }
        
        void move() const override {
            std::cout << "  🐕 " << name_ << " runs happily\n";
        }
    };
    
    class Cat : public Animal {
    public:
        Cat(std::string name) : Animal(std::move(name)) {}
        
        void makeSound() const override {
            std::cout << "  🐱 " << name_ << " says: Meow!\n";
        }
        
        void move() const override {
            std::cout << "  🐱 " << name_ << " prowls silently\n";
        }
    };
    
    std::vector<std::unique_ptr<Animal>> animals;
    animals.push_back(std::make_unique<Dog>("Buddy"));
    animals.push_back(std::make_unique<Cat>("Whiskers"));
    
    std::cout << "\nPolymorphic behavior:\n";
    for (const auto& animal : animals) {
        animal->makeSound();
        animal->move();
    }
    std::cout << "\n";
}

void OOPQuest::demonstratePolymorphism() {
    TutorialHelper::printHeader("Polymorphism in Action");
    
    TutorialHelper::printCode(R"(
// Interface (abstract base class)
class Drawable {
public:
    virtual ~Drawable() = default;
    virtual void draw() const = 0;
    virtual double area() const = 0;
    virtual std::string getType() const = 0;
};

// Concrete implementations
class Circle : public Drawable {
private:
    double radius_;
    
public:
    Circle(double radius) : radius_(radius) {}
    
    void draw() const override {
        std::cout << "Drawing a circle with radius " << radius_ << "\n";
    }
    
    double area() const override {
        return 3.14159 * radius_ * radius_;
    }
    
    std::string getType() const override {
        return "Circle";
    }
};

class Rectangle : public Drawable {
private:
    double width_, height_;
    
public:
    Rectangle(double width, double height) : width_(width), height_(height) {}
    
    void draw() const override {
        std::cout << "Drawing a rectangle " << width_ << "x" << height_ << "\n";
    }
    
    double area() const override {
        return width_ * height_;
    }
    
    std::string getType() const override {
        return "Rectangle";
    }
};

// Function that works with any Drawable
void renderShape(const Drawable& shape) {
    std::cout << "Rendering " << shape.getType() 
              << " (area: " << shape.area() << "): ";
    shape.draw();
}

// Collection of different shapes
void renderAllShapes(const std::vector<std::unique_ptr<Drawable>>& shapes) {
    double totalArea = 0.0;
    for (const auto& shape : shapes) {
        renderShape(*shape);
        totalArea += shape->area();
    }
    std::cout << "Total area: " << totalArea << "\n";
}
)");
    
    std::cout << "Live polymorphism demonstration:\n";
    
    class Shape {
    public:
        virtual ~Shape() = default;
        virtual void describe() const = 0;
        virtual double getArea() const = 0;
    };
    
    class Square : public Shape {
    private:
        double side_;
    public:
        Square(double side) : side_(side) {}
        
        void describe() const override {
            std::cout << "  🟦 Square with side " << side_ 
                      << " (area: " << getArea() << ")\n";
        }
        
        double getArea() const override {
            return side_ * side_;
        }
    };
    
    class Triangle : public Shape {
    private:
        double base_, height_;
    public:
        Triangle(double base, double height) : base_(base), height_(height) {}
        
        void describe() const override {
            std::cout << "  🔺 Triangle with base " << base_ << " and height " << height_
                      << " (area: " << getArea() << ")\n";
        }
        
        double getArea() const override {
            return 0.5 * base_ * height_;
        }
    };
    
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Square>(5.0));
    shapes.push_back(std::make_unique<Triangle>(4.0, 6.0));
    shapes.push_back(std::make_unique<Square>(3.0));
    
    std::cout << "Polymorphic shape processing:\n";
    double totalArea = 0.0;
    for (const auto& shape : shapes) {
        shape->describe();
        totalArea += shape->getArea();
    }
    std::cout << "Total area of all shapes: " << totalArea << "\n\n";
}

void OOPQuest::demonstrateRuleOfFive() {
    TutorialHelper::printHeader("Rule of Five: Resource Management");
    
    TutorialHelper::printCode(R"(
// Rule of Five: If you define any of these, define all five:
// 1. Destructor
// 2. Copy constructor
// 3. Copy assignment operator
// 4. Move constructor
// 5. Move assignment operator

class ResourceManager {
private:
    int* data_;
    size_t size_;
    std::string name_;
    
public:
    // Constructor
    ResourceManager(const std::string& name, size_t size)
        : data_(new int[size]), size_(size), name_(name) {
        std::fill(data_, data_ + size_, 42);
        std::cout << "Created " << name_ << " with " << size_ << " elements\n";
    }
    
    // 1. Destructor
    ~ResourceManager() {
        delete[] data_;
        std::cout << "Destroyed " << name_ << "\n";
    }
    
    // 2. Copy constructor
    ResourceManager(const ResourceManager& other)
        : data_(new int[other.size_]), size_(other.size_), name_(other.name_ + "_copy") {
        std::copy(other.data_, other.data_ + size_, data_);
        std::cout << "Copy constructed " << name_ << "\n";
    }
    
    // 3. Copy assignment operator
    ResourceManager& operator=(const ResourceManager& other) {
        if (this != &other) {
            // Clean up existing resources
            delete[] data_;
            
            // Copy new resources
            size_ = other.size_;
            name_ = other.name_ + "_assigned";
            data_ = new int[size_];
            std::copy(other.data_, other.data_ + size_, data_);
            
            std::cout << "Copy assigned " << name_ << "\n";
        }
        return *this;
    }
    
    // 4. Move constructor
    ResourceManager(ResourceManager&& other) noexcept
        : data_(other.data_), size_(other.size_), name_(std::move(other.name_)) {
        other.data_ = nullptr;
        other.size_ = 0;
        std::cout << "Move constructed " << name_ << "\n";
    }
    
    // 5. Move assignment operator
    ResourceManager& operator=(ResourceManager&& other) noexcept {
        if (this != &other) {
            // Clean up existing resources
            delete[] data_;
            
            // Take ownership of other's resources
            data_ = other.data_;
            size_ = other.size_;
            name_ = std::move(other.name_);
            
            // Leave other in valid but unspecified state
            other.data_ = nullptr;
            other.size_ = 0;
            
            std::cout << "Move assigned " << name_ << "\n";
        }
        return *this;
    }
    
    // Utility functions
    size_t size() const { return size_; }
    const std::string& name() const { return name_; }
    int& operator[](size_t index) { return data_[index]; }
    const int& operator[](size_t index) const { return data_[index]; }
};
)");
    
    std::cout << "Live Rule of Five demonstration:\n";
    
    class SimpleResource {
    private:
        std::unique_ptr<int[]> data_;
        size_t size_;
        std::string name_;
        
    public:
        // Constructor
        SimpleResource(std::string name, size_t size) 
            : data_(std::make_unique<int[]>(size)), size_(size), name_(std::move(name)) {
            std::cout << "  🔧 Created " << name_ << " (" << size_ << " elements)\n";
        }
        
        // Destructor (automatically handled by unique_ptr)
        ~SimpleResource() {
            std::cout << "  🗑️  Destroyed " << name_ << "\n";
        }
        
        // Copy constructor
        SimpleResource(const SimpleResource& other)
            : data_(std::make_unique<int[]>(other.size_)), size_(other.size_), 
              name_(other.name_ + "_copy") {
            std::copy(other.data_.get(), other.data_.get() + size_, data_.get());
            std::cout << "  📋 Copy constructed " << name_ << "\n";
        }
        
        // Copy assignment
        SimpleResource& operator=(const SimpleResource& other) {
            if (this != &other) {
                data_ = std::make_unique<int[]>(other.size_);
                size_ = other.size_;
                name_ = other.name_ + "_assigned";
                std::copy(other.data_.get(), other.data_.get() + size_, data_.get());
                std::cout << "  📝 Copy assigned " << name_ << "\n";
            }
            return *this;
        }
        
        // Move constructor
        SimpleResource(SimpleResource&& other) noexcept
            : data_(std::move(other.data_)), size_(other.size_), name_(std::move(other.name_)) {
            other.size_ = 0;
            std::cout << "  ⚡ Move constructed " << name_ << "\n";
        }
        
        // Move assignment
        SimpleResource& operator=(SimpleResource&& other) noexcept {
            if (this != &other) {
                data_ = std::move(other.data_);
                size_ = other.size_;
                name_ = std::move(other.name_);
                other.size_ = 0;
                std::cout << "  🔄 Move assigned " << name_ << "\n";
            }
            return *this;
        }
        
        const std::string& getName() const { return name_; }
        size_t size() const { return size_; }
    };
    
    std::cout << "Testing Rule of Five operations:\n";
    
    {
        SimpleResource original("Original", 100);
        SimpleResource copied = original;              // Copy constructor
        SimpleResource moved = std::move(original);    // Move constructor
        
        SimpleResource assigned("Temp", 50);
        assigned = copied;                             // Copy assignment
        
        SimpleResource moveAssigned("Temp2", 25);
        moveAssigned = std::move(moved);               // Move assignment
        
        std::cout << "  Final state - moveAssigned name: " << moveAssigned.getName() << "\n";
    } // All destructors called here
    
    std::cout << "\n";
}

}  // namespace tutorial
