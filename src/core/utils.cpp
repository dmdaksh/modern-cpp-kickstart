/**
 * @file utils.cpp
 * @brief Implementation of core utility classes and functions
 * 
 * This file contains the implementation of reusable utility classes
 * that demonstrate modern C++ best practices including RAII,
 * type safety, and exception safety.
 * 
 * @author Modern C++ Starter Template
 * @date 2025
 */

#include "core/utils.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <unordered_map>
#include <typeindex>
#include <cstdarg>

namespace core {

// Config implementation
bool Config::has(const std::string& key) const {
    return values_.find(key) != values_.end();
}

void Config::remove(const std::string& key) {
    values_.erase(key);
}

// Logger implementation
Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::setLevel(LogLevel level) {
    currentLevel_ = level;
}

template<typename... Args>
void Logger::debug(const std::string& format, Args&&... args) {
    log(LogLevel::Debug, format, std::forward<Args>(args)...);
}

template<typename... Args>
void Logger::info(const std::string& format, Args&&... args) {
    log(LogLevel::Info, format, std::forward<Args>(args)...);
}

template<typename... Args>
void Logger::warning(const std::string& format, Args&&... args) {
    log(LogLevel::Warning, format, std::forward<Args>(args)...);
}

template<typename... Args>
void Logger::error(const std::string& format, Args&&... args) {
    log(LogLevel::Error, format, std::forward<Args>(args)...);
}

template<typename... Args>
void Logger::log(LogLevel level, const std::string& format, Args&&... args) {
    if (level < currentLevel_) {
        return;
    }
    
    const char* levelStr = "INFO";
    const char* levelEmoji = "ℹ️";
    
    switch (level) {
        case LogLevel::Debug:
            levelStr = "DEBUG";
            levelEmoji = "🐛";
            break;
        case LogLevel::Info:
            levelStr = "INFO";
            levelEmoji = "ℹ️";
            break;
        case LogLevel::Warning:
            levelStr = "WARN";
            levelEmoji = "⚠️";
            break;
        case LogLevel::Error:
            levelStr = "ERROR";
            levelEmoji = "❌";
            break;
    }
    
    // Simple format string replacement (for demonstration)
    // In a real implementation, you might use std::format (C++20) or a formatting library
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    
    std::cout << "[" << std::put_time(std::localtime(&time_t), "%H:%M:%S") << "] "
              << levelEmoji << " " << levelStr << ": " << format << std::endl;
}

// Explicit template instantiations for common types
template void Config::set<int>(const std::string&, int&&);
template void Config::set<std::string>(const std::string&, std::string&&);
template void Config::set<double>(const std::string&, double&&);
template void Config::set<bool>(const std::string&, bool&&);

template int Config::get<int>(const std::string&) const;
template std::string Config::get<std::string>(const std::string&) const;
template double Config::get<double>(const std::string&) const;
template bool Config::get<bool>(const std::string&) const;

template void Logger::debug<>(const std::string&);
template void Logger::info<>(const std::string&);
template void Logger::warning<>(const std::string&);
template void Logger::error<>(const std::string&);

}  // namespace core
