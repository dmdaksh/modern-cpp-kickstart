# 📚 Modern C++ Starter Template - Complete Documentation

## 🚀 Quick Start

### Prerequisites

- C++20 compatible compiler (GCC 10+, Clang 12+, MSVC 2022+)
- CMake 3.20+
- Git

### Build & Run

```bash
# Clone and build
git clone <your-repo>
cd cpp-starter
chmod +x scripts/build.sh
./scripts/build.sh build

# Run tutorial
./scripts/build.sh run

# Run tests
./scripts/build.sh test
```

## 🏗️ Project Architecture

```text
cpp-starter/
├── README.md                   # Main project documentation
├── DOCS.md                    # This comprehensive guide
├── CMakeLists.txt             # Root CMake configuration
├── scripts/build.sh           # Build automation script
│
├── include/                   # Header files
│   ├── core/utils.hpp         # Core utilities (RAII, Config, Logger)
│   └── tutorial/              # Tutorial framework headers
│
├── src/                       # Source files
│   ├── main.cpp              # Tutorial entry point
│   ├── core/utils.cpp        # Core utilities implementation
│   └── tutorial/             # Tutorial quest implementations
│
├── tests/                     # Unit tests
│   ├── test_core_utils.cpp   # Core utilities tests
│   └── test_tutorial_quest.cpp # Tutorial tests
│
└── examples/                  # Standalone examples
    └── smart_pointers_demo.cpp # Smart pointer demonstration
```

### Design Principles

- **Modern C++20**: Latest standards and best practices
- **RAII**: Resource management through constructors/destructors
- **Type Safety**: Strong typing and compile-time error detection
- **Exception Safety**: Proper error handling patterns
- **Memory Safety**: Smart pointers and automatic resource management

## 📖 API Reference

### Core Utilities (`include/core/utils.hpp`)

#### `RaiiWrapper<T>`

Automatic resource management with custom cleanup.

```cpp
#include "core/utils.hpp"

// Example: File handle management
auto file = RaiiWrapper<FILE*>(
    fopen("data.txt", "r"),
    [](FILE* f) { if (f) fclose(f); }
);

if (file.get()) {
    // Use file safely - automatically closed when out of scope
}
```

**Methods:**

- `get() -> T&` - Access wrapped resource
- `reset(T new_resource)` - Replace resource
- `release() -> T` - Release ownership

#### Config

Type-safe key-value configuration storage.

```cpp
Config config;
config.set("window_width", 1920);
config.set("app_name", std::string("MyApp"));

auto width = config.get<int>("window_width", 800);  // Returns 1920
auto name = config.get<std::string>("app_name");    // Returns "MyApp"
```

**Methods:**

- `set<T>(key, value)` - Store typed value
- `get<T>(key, default_value)` - Retrieve with default
- `get<T>(key)` - Retrieve (throws if missing)
- `has(key) -> bool` - Check existence

#### Logger

Thread-safe singleton logging system.

```cpp
auto& logger = Logger::getInstance();
logger.setLevel(Logger::Level::INFO);

logger.debug("Debug information");
logger.info("Application started");
logger.warning("Non-critical issue");
logger.error("Error occurred");
```

**Log Levels:** DEBUG < INFO < WARNING < ERROR

## 🎓 Tutorial System

### Learning Path

1. **Basics Quest** - Variables, functions, control flow
2. **Memory Quest** - Pointers, references, smart pointers
3. **OOP Quest** - Classes, inheritance, polymorphism
4. **STL Quest** - Containers, algorithms, iterators
5. **Templates Quest** - Generic programming, metaprogramming
6. **Concurrency Quest** - Threads, synchronization, futures

### Tutorial Features

- **Interactive Exercises**: Hands-on coding challenges
- **Progressive Difficulty**: From beginner to advanced
- **Immediate Feedback**: Instant validation and hints
- **Best Practices**: Modern C++ patterns and idioms

### Running Tutorials

```bash
./scripts/build.sh run

# Or manually:
./build/src/cpp_tutorial
```

## 🔧 Build System

### CMake Configuration

- **Minimum Version**: CMake 3.20
- **C++ Standard**: C++20
- **Compiler Warnings**: Comprehensive warning flags
- **Testing**: Google Test integration
- **Tools**: clang-format, clang-tidy support

### Build Script Commands

```bash
./scripts/build.sh help       # Show all commands
./scripts/build.sh build      # Build project
./scripts/build.sh test       # Run tests
./scripts/build.sh run        # Run tutorial
./scripts/build.sh clean      # Clean build
./scripts/build.sh format     # Format code
./scripts/build.sh analyze    # Static analysis
```

### Manual Build

```bash
mkdir build && cd build
cmake ..
make -j$(nproc)
make test
```

## 🧪 Testing

### Running Tests

```bash
# All tests
./scripts/build.sh test

# Specific test categories
ctest -R CoreUtils
ctest -R TutorialQuest
```

### Test Structure

- **15 total tests** covering all functionality
- **Core utilities tests**: RAII, Config, Logger
- **Tutorial tests**: Quest system validation
- **Example tests**: Smart pointer demonstrations

## 🛠️ Development Guidelines

### Code Style

- **Formatting**: Use clang-format (provided .clang-format)
- **Naming**: snake_case for variables, PascalCase for classes
- **Headers**: Always include guards or #pragma once
- **Documentation**: Doxygen-style comments for public APIs

### Best Practices

- Use RAII for all resource management
- Prefer smart pointers over raw pointers
- Use const-correctness throughout
- Implement proper exception safety
- Follow single responsibility principle

### Contributing

1. Fork the repository
2. Create feature branch: `git checkout -b feature/amazing-feature`
3. Write tests for new functionality
4. Ensure all tests pass: `./scripts/build.sh test`
5. Format code: `./scripts/build.sh format`
6. Commit changes: `git commit -m 'Add amazing feature'`
7. Push branch: `git push origin feature/amazing-feature`
8. Open Pull Request

## 🚀 Converting to Production Template

### Keep Core Components

```text
include/core/utils.hpp         # Core utilities
src/core/utils.cpp            # Implementation
tests/test_core_utils.cpp     # Tests
scripts/build.sh              # Build automation
CMakeLists.txt                # Build configuration
```

### Remove Tutorial System

```bash
# Quick conversion (1 minute)
rm -rf src/tutorial/ include/tutorial/
rm src/main.cpp tests/test_tutorial_quest.cpp

# Update CMakeLists.txt to remove tutorial targets
# Create your own main.cpp using core utilities
```

### Create Your Application

```cpp
// src/main.cpp
#include "core/utils.hpp"
#include <iostream>

int main() {
    auto& logger = Logger::getInstance();
    logger.info("Application starting...");
    
    Config config;
    config.set("version", std::string("1.0.0"));
    
    // Your application logic here
    
    logger.info("Application finished.");
    return 0;
}
```

## 🔍 Troubleshooting

### Common Build Issues

#### CMake not found

```bash
# macOS
brew install cmake

# Ubuntu/Debian
sudo apt-get install cmake

# Windows
# Download from https://cmake.org/download/
```

#### Compiler not C++20 compatible

```bash
# Check compiler version
g++ --version    # Should be 10+
clang++ --version # Should be 12+

# Update if needed (Ubuntu)
sudo apt-get install gcc-11 g++-11
```

#### Tests failing

```bash
# Clean rebuild
./scripts/build.sh clean
./scripts/build.sh build
./scripts/build.sh test

# Check specific test output
ctest --verbose
```

### Runtime Issues

#### Permission denied on scripts

```bash
chmod +x scripts/build.sh
```

#### Missing shared libraries

```bash
# Check dependencies
ldd build/src/cpp_tutorial

# Update library path if needed
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./build/lib
```

### Performance Optimization

#### Debug vs Release builds

```bash
# Debug (default)
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Release (optimized)
cmake -DCMAKE_BUILD_TYPE=Release ..
```

#### Compiler optimizations

```bash
# High optimization
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-O3 -DNDEBUG" ..
```

## 📊 Project Statistics

### Code Metrics

- **17 source files** (.cpp/.hpp)
- **15 unit tests** (100% pass rate)
- **6 tutorial quests** (progressive difficulty)
- **3 core utilities** (production-ready)

### Quality Metrics

- ✅ Modern C++20 standards
- ✅ RAII resource management
- ✅ Exception safety guarantees
- ✅ Memory safety with smart pointers
- ✅ Thread-safe logging
- ✅ Comprehensive test coverage

## 🎯 Next Steps

### For Learning

1. Start with the tutorial: `./scripts/build.sh run`
2. Work through all 6 quest levels
3. Experiment with the examples
4. Contribute your own quest ideas

### For Development

1. Remove tutorial components (see conversion guide above)
2. Build your application using core utilities
3. Extend utilities as needed for your domain
4. Maintain test coverage for new features

## 📚 Additional Resources

### C++20 Features Used

- Concepts and constraints
- Ranges and views
- Modules (where supported)
- Coroutines (in advanced examples)
- Template improvements

### External Dependencies

- **Google Test**: Unit testing framework
- **CMake**: Build system generator
- **clang-format**: Code formatting
- **clang-tidy**: Static analysis

### Learning Resources

- [CPP Reference](https://en.cppreference.com/)
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/)
- [Modern C++ best practices](https://github.com/cpp-best-practices)

---

### This project serves as both a learning platform and a production-ready template. Choose your path and start building amazing C++ applications! 🚀
