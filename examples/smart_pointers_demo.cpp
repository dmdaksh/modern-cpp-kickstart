/**
 * @file smart_pointers_demo.cpp
 * @brief Comprehensive demonstration of modern C++ smart pointers
 * @author Modern C++ Starter Template
 * @date 2025
 * 
 * This example demonstrates:
 * - Basic smart pointer usage (unique_ptr, shared_ptr, weak_ptr)
 * - Custom deleters for specialized resource management
 * - Factory pattern with smart pointers
 * - Avoiding circular references with weak_ptr
 * - RAII principles and best practices
 */

#include <iostream>
#include <memory>
#include <vector>
#include <string>

// Example 1: Basic smart pointer usage
void basicSmartPointers() {
    std::cout << "=== Basic Smart Pointers ===\n";
    
    // unique_ptr - single ownership
    auto uniqueInt = std::make_unique<int>(42);
    std::cout << "unique_ptr value: " << *uniqueInt << "\n";
    
    // shared_ptr - shared ownership
    auto shared1 = std::make_shared<std::string>("Shared Resource");
    auto shared2 = shared1;  // Share ownership
    std::cout << "shared_ptr value: " << *shared1 << "\n";
    std::cout << "Reference count: " << shared1.use_count() << "\n";
    
    // weak_ptr - non-owning observer
    std::weak_ptr<std::string> weak = shared1;
    if (auto locked = weak.lock()) {
        std::cout << "weak_ptr access: " << *locked << "\n";
    }
}

// Example 2: Custom deleter
void customDeleterExample() {
    std::cout << "\n=== Custom Deleter ===\n";
    
    auto customDeleter = [](int* ptr) {
        std::cout << "Custom deleting value: " << *ptr << "\n";
        delete ptr;
    };
    
    std::unique_ptr<int, decltype(customDeleter)> ptr(new int(99), customDeleter);
    std::cout << "Value: " << *ptr << "\n";
    // Custom deleter will be called when ptr goes out of scope
}

// Example 3: Factory pattern with smart pointers
class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
    virtual std::string getType() const = 0;
};

class Circle : public Shape {
private:
    double radius_;
public:
    Circle(double radius) : radius_(radius) {}
    void draw() const override {
        std::cout << "Drawing circle with radius " << radius_ << "\n";
    }
    std::string getType() const override { return "Circle"; }
};

class Rectangle : public Shape {
private:
    double width_, height_;
public:
    Rectangle(double width, double height) : width_(width), height_(height) {}
    void draw() const override {
        std::cout << "Drawing rectangle " << width_ << "x" << height_ << "\n";
    }
    std::string getType() const override { return "Rectangle"; }
};

// Factory function returning unique_ptr
std::unique_ptr<Shape> createShape(const std::string& type, double param1, double param2 = 0) {
    if (type == "circle") {
        return std::make_unique<Circle>(param1);
    } else if (type == "rectangle") {
        return std::make_unique<Rectangle>(param1, param2);
    }
    return nullptr;
}

void factoryExample() {
    std::cout << "\n=== Factory Pattern ===\n";
    
    std::vector<std::unique_ptr<Shape>> shapes;
    
    shapes.push_back(createShape("circle", 5.0));
    shapes.push_back(createShape("rectangle", 3.0, 4.0));
    shapes.push_back(createShape("circle", 2.5));
    
    for (const auto& shape : shapes) {
        if (shape) {
            std::cout << "Shape: " << shape->getType() << " - ";
            shape->draw();
        }
    }
}

// Example 4: Avoiding circular references with weak_ptr
class Node {
public:
    std::string data;
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> parent;  // Use weak_ptr to avoid cycles
    
    Node(std::string data) : data(std::move(data)) {}
    
    ~Node() {
        std::cout << "Destroying node: " << data << "\n";
    }
};

void avoidCircularReferences() {
    std::cout << "\n=== Avoiding Circular References ===\n";
    
    auto parent = std::make_shared<Node>("Parent");
    auto child1 = std::make_shared<Node>("Child1");
    auto child2 = std::make_shared<Node>("Child2");
    
    // Set up parent-child relationships
    parent->next = child1;
    child1->parent = parent;  // weak_ptr doesn't increase reference count
    child1->next = child2;
    child2->parent = child1;
    
    std::cout << "Parent ref count: " << parent.use_count() << "\n";
    std::cout << "Child1 ref count: " << child1.use_count() << "\n";
    
    // Check if parent is still alive from child's perspective
    if (auto parentPtr = child1->parent.lock()) {
        std::cout << "Child1 can access parent: " << parentPtr->data << "\n";
    }
    
    // Objects will be properly destroyed when they go out of scope
}

int main() {
    try {
        basicSmartPointers();
        customDeleterExample();
        factoryExample();
        avoidCircularReferences();
        
        std::cout << "\n=== All examples completed successfully! ===\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}
