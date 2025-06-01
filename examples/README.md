# 💡 C++ Examples

Standalone examples demonstrating modern C++ concepts.

## Available Examples

### Smart Pointers Demo (`smart_pointers_demo.cpp`)

- Modern C++ memory management with `unique_ptr`, `shared_ptr`, and `weak_ptr`
- Custom deleters and circular reference prevention  
- RAII principles and best practices

## 🏗️ Building and Running

```bash
# Build specific example
g++ -std=c++20 -I../include smart_pointers_demo.cpp -o smart_pointers_demo

# Or use project build system
cd .. && ./scripts/build.sh build
./build/smart_pointers_demo
```

## 📚 Full Documentation

See [DOCS.md](../DOCS.md) for complete API reference and tutorials.
