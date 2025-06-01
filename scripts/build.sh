#!/bin/bash

# Modern C++ Project Build Script
# This script provides common build tasks for the C++ tutorial project

set -e  # Exit on any error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Project root directory
PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="$PROJECT_ROOT/build"

print_header() {
    echo -e "${BLUE}========================================${NC}"
    echo -e "${BLUE}$1${NC}"
    echo -e "${BLUE}========================================${NC}"
}

print_success() {
    echo -e "${GREEN}✅ $1${NC}"
}

print_warning() {
    echo -e "${YELLOW}⚠️  $1${NC}"
}

print_error() {
    echo -e "${RED}❌ $1${NC}"
}

# Function to create build directory
setup_build_dir() {
    if [ ! -d "$BUILD_DIR" ]; then
        print_warning "Creating build directory..."
        mkdir -p "$BUILD_DIR"
    fi
}

# Function to configure project
configure() {
    print_header "Configuring Project"
    setup_build_dir
    
    cd "$BUILD_DIR"
    
    local build_type="${1:-Release}"
    print_warning "Build type: $build_type"
    
    cmake -DCMAKE_BUILD_TYPE="$build_type" \
          -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
          "$PROJECT_ROOT"
    
    print_success "Project configured successfully"
}

# Function to build project
build() {
    print_header "Building Project"
    
    if [ ! -f "$BUILD_DIR/Makefile" ]; then
        print_warning "No Makefile found. Running configure first..."
        configure
    fi
    
    cd "$BUILD_DIR"
    
    local jobs="${1:-$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)}"
    print_warning "Building with $jobs parallel jobs..."
    
    make -j"$jobs"
    
    print_success "Build completed successfully"
}

# Function to run tests
test() {
    print_header "Running Tests"
    
    if [ ! -f "$BUILD_DIR/tests/cpp_tutorial_tests" ]; then
        print_warning "Tests not built. Building first..."
        build
    fi
    
    cd "$BUILD_DIR"
    ctest --verbose --output-on-failure
    
    print_success "All tests passed"
}

# Function to run the tutorial
run() {
    print_header "Running C++ Tutorial"

    if [ ! -f "$BUILD_DIR/src/cpp_tutorial" ]; then
        print_warning "Tutorial not built. Building first..."
        build
    fi

    cd "$BUILD_DIR"
    ./src/cpp_tutorial
}

# Function to clean build
clean() {
    print_header "Cleaning Build"
    
    if [ -d "$BUILD_DIR" ]; then
        rm -rf "$BUILD_DIR"
        print_success "Build directory cleaned"
    else
        print_warning "Build directory already clean"
    fi
}

# Function to format code
format() {
    print_header "Formatting Code"
    
    if ! command -v clang-format &> /dev/null; then
        print_error "clang-format not found. Please install it first."
        return 1
    fi
    
    find "$PROJECT_ROOT/src" "$PROJECT_ROOT/include" "$PROJECT_ROOT/tests" \
         -name "*.cpp" -o -name "*.hpp" -o -name "*.h" | \
    xargs clang-format -i
    
    print_success "Code formatted successfully"
}

# Function to run static analysis
analyze() {
    print_header "Running Static Analysis"
    
    if ! command -v clang-tidy &> /dev/null; then
        print_error "clang-tidy not found. Please install it first."
        return 1
    fi
    
    if [ ! -f "$BUILD_DIR/compile_commands.json" ]; then
        print_warning "compile_commands.json not found. Configuring first..."
        configure
        build
    fi
    
    cd "$PROJECT_ROOT"
    
    find src tests -name "*.cpp" | \
    xargs clang-tidy -p "$BUILD_DIR"
    
    print_success "Static analysis completed"
}

# Function to build examples
examples() {
    print_header "Building Examples"
    
    local example_build_dir="$BUILD_DIR/examples"
    mkdir -p "$example_build_dir"
    
    for example in "$PROJECT_ROOT/examples"/*.cpp; do
        if [ -f "$example" ]; then
            local basename=$(basename "$example" .cpp)
            print_warning "Building example: $basename"
            
            g++ -std=c++20 -Wall -Wextra -O2 \
                -I"$PROJECT_ROOT/include" \
                "$example" \
                -o "$example_build_dir/$basename"
        fi
    done
    
    print_success "Examples built successfully"
    echo "Examples available in: $example_build_dir"
}

# Function to show help
help() {
    cat << EOF
🚀 Modern C++ Tutorial Build Script

Usage: $0 <command> [options]

Commands:
    configure [Debug|Release]  Configure the project (default: Release)
    build [jobs]              Build the project (default: auto-detect CPU cores)
    test                      Run all tests
    run                       Run the tutorial application
    clean                     Clean build directory
    format                    Format all source code with clang-format
    analyze                   Run static analysis with clang-tidy
    examples                  Build standalone examples
    help                      Show this help message

Examples:
    $0 configure Debug        Configure for debug build
    $0 build 8               Build using 8 parallel jobs
    $0 test                  Run all tests
    $0 run                   Start the tutorial
    $0 clean && $0 build     Clean build and rebuild

Dependencies:
    - CMake 3.20+
    - C++20 compatible compiler (GCC 10+, Clang 12+, MSVC 2022+)
    - clang-format (optional, for formatting)
    - clang-tidy (optional, for static analysis)

EOF
}

# Main script logic
case "${1:-help}" in
    configure)
        configure "${2:-Release}"
        ;;
    build)
        build "${2}"
        ;;
    test)
        test
        ;;
    run)
        run
        ;;
    clean)
        clean
        ;;
    format)
        format
        ;;
    analyze)
        analyze
        ;;
    examples)
        examples
        ;;
    help|--help|-h)
        help
        ;;
    *)
        print_error "Unknown command: $1"
        echo "Run '$0 help' for usage information."
        exit 1
        ;;
esac
