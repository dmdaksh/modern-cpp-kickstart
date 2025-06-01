/**
 * @file utils.hpp
 * @brief Core utility classes and functions for modern C++ development
 * 
 * This header provides a collection of reusable utility classes that demonstrate
 * modern C++ best practices including:
 * - RAII resource management
 * - Type-safe configuration systems
 * - Modern logging facilities
 * - Template programming techniques
 * - Exception safety guarantees
 * 
 * All utilities are designed to be production-ready and follow the C++ Core Guidelines.
 * 
 * @author Modern C++ Starter Template
 * @date 2025
 */

#pragma once

#include <memory>
#include <vector>
#include <string>
#include <functional>
#include <unordered_map>
#include <typeindex>
#include <stdexcept>
#include <chrono>

namespace core {

/**
 * @brief Modern C++ utility functions and helpers
 * 
 * This namespace contains reusable utilities that demonstrate
 * modern C++ best practices and can be used in real projects.
 */

/**
 * @brief RAII wrapper for any resource with custom deleter
 * 
 * Example usage:
 * auto fileHandle = makeRaiiWrapper(fopen("file.txt", "r"), fclose);
 */
template<typename T, typename Deleter>
class RaiiWrapper {
public:
    explicit RaiiWrapper(T resource, Deleter deleter) 
        : resource_(resource), deleter_(deleter) {}
    
    ~RaiiWrapper() {
        if (resource_) {
            deleter_(resource_);
        }
    }
    
    // Non-copyable but movable
    RaiiWrapper(const RaiiWrapper&) = delete;
    RaiiWrapper& operator=(const RaiiWrapper&) = delete;
    
    RaiiWrapper(RaiiWrapper&& other) noexcept 
        : resource_(other.resource_), deleter_(std::move(other.deleter_)) {
        other.resource_ = nullptr;
    }
    
    RaiiWrapper& operator=(RaiiWrapper&& other) noexcept {
        if (this != &other) {
            if (resource_) {
                deleter_(resource_);
            }
            resource_ = other.resource_;
            deleter_ = std::move(other.deleter_);
            other.resource_ = nullptr;
        }
        return *this;
    }
    
    T get() const { return resource_; }
    explicit operator bool() const { return resource_ != nullptr; }
    
    void reset() {
        if (resource_) {
            deleter_(resource_);
            resource_ = nullptr;
        }
    }
    
private:
    T resource_;
    Deleter deleter_;
};

template<typename T, typename Deleter>
auto makeRaiiWrapper(T resource, Deleter deleter) {
    return RaiiWrapper<T, Deleter>(resource, deleter);
}

/**
 * @brief Type-safe configuration system
 */
class Config {
public:
    template<typename T>
    void set(const std::string& key, T&& value);
    
    template<typename T>
    T get(const std::string& key) const;
    
    template<typename T>
    T getOrDefault(const std::string& key, T&& defaultValue) const;
    
    bool has(const std::string& key) const;
    void remove(const std::string& key);    private:
        class ConfigValue {
        public:
            // Default constructor for container usage
            ConfigValue() : type_(std::type_index(typeid(void))) {}
            
            template<typename T>
            ConfigValue(T&& value) 
                : type_(std::type_index(typeid(typename std::decay<T>::type))) {
                using DecayedT = typename std::decay<T>::type;
                data_ = std::make_shared<DecayedT>(std::forward<T>(value));
            }
            
            template<typename T>
            T as() const {
                using DecayedT = typename std::decay<T>::type;
                if (type_ != std::type_index(typeid(DecayedT))) {
                    throw std::runtime_error("Type mismatch in Config::get()");
                }
                return *static_cast<DecayedT*>(data_.get());
            }
            
        private:
            std::shared_ptr<void> data_;
            std::type_index type_;
        };
        
        std::unordered_map<std::string, ConfigValue> values_;
};

// Template method implementations for Config
template<typename T>
void Config::set(const std::string& key, T&& value) {
    values_[key] = ConfigValue(std::forward<T>(value));
}

template<typename T>
T Config::get(const std::string& key) const {
    auto it = values_.find(key);
    if (it == values_.end()) {
        throw std::runtime_error("Key not found: " + key);
    }
    return it->second.template as<T>();
}

template<typename T>
T Config::getOrDefault(const std::string& key, T&& defaultValue) const {
    auto it = values_.find(key);
    if (it == values_.end()) {
        return std::forward<T>(defaultValue);
    }
    return it->second.template as<T>();
}

/**
 * @brief Simple logger with different levels
 */
enum class LogLevel {
    Debug,
    Info,
    Warning,
    Error
};

class Logger {
public:
    static Logger& getInstance();
    
    void setLevel(LogLevel level);
    
    template<typename... Args>
    void debug(const std::string& format, Args&&... args);
    
    template<typename... Args>
    void info(const std::string& format, Args&&... args);
    
    template<typename... Args>
    void warning(const std::string& format, Args&&... args);
    
    template<typename... Args>
    void error(const std::string& format, Args&&... args);
    
private:
    Logger() = default;
    LogLevel currentLevel_ = LogLevel::Info;
    
    template<typename... Args>
    void log(LogLevel level, const std::string& format, Args&&... args);
};

}  // namespace core
