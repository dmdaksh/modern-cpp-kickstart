#include <gtest/gtest.h>
#include "core/utils.hpp"
#include <thread>
#include <chrono>

class CoreUtilsTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code if needed
    }
    
    void TearDown() override {
        // Cleanup code if needed
    }
};

// Test RAII Wrapper
TEST_F(CoreUtilsTest, RaiiWrapperBasicUsage) {
    bool wasDeleted = false;
    
    {
        auto deleter = [&wasDeleted](int* ptr) {
            wasDeleted = true;
            delete ptr;
        };
        
        auto wrapper = core::makeRaiiWrapper(new int(42), deleter);
        EXPECT_EQ(*wrapper.get(), 42);
        EXPECT_TRUE(wrapper);
        EXPECT_FALSE(wasDeleted);
    }
    
    EXPECT_TRUE(wasDeleted);
}

TEST_F(CoreUtilsTest, RaiiWrapperMoveSemantics) {
    bool wasDeleted = false;
    int* originalPtr = new int(100);
    
    auto deleter = [&wasDeleted](int* ptr) {
        wasDeleted = true;
        delete ptr;
    };
    
    auto wrapper1 = core::makeRaiiWrapper(originalPtr, deleter);
    EXPECT_EQ(wrapper1.get(), originalPtr);
    
    auto wrapper2 = std::move(wrapper1);
    EXPECT_EQ(wrapper2.get(), originalPtr);
    EXPECT_EQ(wrapper1.get(), nullptr);  // After move
    EXPECT_FALSE(wasDeleted);
    
    // Test destruction
    wrapper2.reset();
    EXPECT_TRUE(wasDeleted);  // Should be deleted now
}

// Test Config System
TEST_F(CoreUtilsTest, ConfigBasicOperations) {
    core::Config config;
    
    // Test setting and getting different types
    config.set("name", std::string("TestApp"));
    config.set("version", 1.0);
    config.set("debug", true);
    config.set("maxConnections", 100);
    
    EXPECT_EQ(config.get<std::string>("name"), "TestApp");
    EXPECT_DOUBLE_EQ(config.get<double>("version"), 1.0);
    EXPECT_TRUE(config.get<bool>("debug"));
    EXPECT_EQ(config.get<int>("maxConnections"), 100);
    
    EXPECT_TRUE(config.has("name"));
    EXPECT_FALSE(config.has("nonexistent"));
}

TEST_F(CoreUtilsTest, ConfigDefaultValues) {
    core::Config config;
    
    // Test default values for non-existent keys
    EXPECT_EQ(config.getOrDefault("timeout", 30), 30);
    EXPECT_EQ(config.getOrDefault("host", std::string("localhost")), "localhost");
    
    // Test that existing values override defaults
    config.set("timeout", 60);
    EXPECT_EQ(config.getOrDefault("timeout", 30), 60);
}

TEST_F(CoreUtilsTest, ConfigTypeSafety) {
    core::Config config;
    config.set("value", 42);
    
    // This should throw because we're trying to get an int as a string
    EXPECT_THROW(config.get<std::string>("value"), std::runtime_error);
    
    // This should throw because the key doesn't exist
    EXPECT_THROW(config.get<int>("nonexistent"), std::runtime_error);
}

// Test Logger
TEST_F(CoreUtilsTest, LoggerSingleton) {
    auto& logger1 = core::Logger::getInstance();
    auto& logger2 = core::Logger::getInstance();
    
    EXPECT_EQ(&logger1, &logger2);  // Should be the same instance
}

TEST_F(CoreUtilsTest, LoggerLevels) {
    auto& logger = core::Logger::getInstance();
    
    // Test that we can set different log levels without crashing
    logger.setLevel(core::LogLevel::Debug);
    logger.debug("Debug message");
    logger.info("Info message");
    logger.warning("Warning message");
    logger.error("Error message");
    
    logger.setLevel(core::LogLevel::Error);
    logger.debug("This debug message should not appear");
    logger.error("This error message should appear");
    
    // Reset to info level for other tests
    logger.setLevel(core::LogLevel::Info);
}
