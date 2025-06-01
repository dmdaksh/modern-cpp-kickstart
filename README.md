# 🚀 Modern C++ Starter Template

[![C++](https://img.shields.io/badge/C%2B%2B-20-blue.svg)](https://isocpp.org/)
[![CMake](https://img.shields.io/badge/CMake-3.20%2B-green.svg)](https://cmake.org/)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

A **clean, modern C++ starter template** with interactive tutorial system and production-ready utilities.

## 🚀 Quick Start

```bash
# Clone and build
git clone <your-repo>
cd cpp-starter
chmod +x scripts/build.sh
./scripts/build.sh build

# Run interactive tutorial
./scripts/build.sh run

# Run tests
./scripts/build.sh test
```

## ✨ Features

- **🎓 Interactive Tutorial**: 6 progressive quests from basics to advanced C++
- **🏗️ Modern Build System**: CMake 3.20+ with cross-platform support
- **🛠️ Production Utilities**: RAII wrappers, config system, thread-safe logging
- **🔧 Developer Tools**: Automated formatting, testing, and static analysis

## 📚 Complete Documentation

**📖 [Full Documentation](DOCS.md)** - Everything you need in one place

## 🎯 Two Usage Modes

### 🎓 Learning Mode

```bash
./scripts/build.sh run  # Interactive C++ tutorial
```

### 🚀 Production Mode

```bash
# Quick conversion to clean template
rm -rf src/tutorial/ include/tutorial/
rm src/main.cpp tests/test_tutorial_quest.cpp
# Create your application using core utilities
```

## 🏆 Quality

- ✅ 15 unit tests (100% pass rate)
- ✅ Modern C++20 standards
- ✅ Memory & exception safety
- ✅ Cross-platform compatibility

## 📄 License

MIT License - see [LICENSE](LICENSE) for details.

---

### Ready to build amazing C++ applications? 🚀
