#include <gtest/gtest.h>
#include "tutorial/quest.hpp"
#include "tutorial/quests.hpp"
#include <sstream>
#include <memory>

class MockQuest : public tutorial::Quest {
private:
    bool shouldComplete_;
    bool started_ = false;
    
public:
    MockQuest(const std::string& name, bool shouldComplete = true) 
        : Quest(name, "Mock quest for testing", 0), shouldComplete_(shouldComplete) {}
    
    void start() override {
        started_ = true;
        if (shouldComplete_) {
            markCompleted();
        }
    }
    
    bool isCompleted() const override {
        return shouldComplete_ && started_;
    }
    
    bool wasStarted() const { return started_; }
};

class TutorialQuestTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Redirect cout to capture output
        originalCout = std::cout.rdbuf();
        std::cout.rdbuf(testOutput.rdbuf());
    }
    
    void TearDown() override {
        // Restore cout
        std::cout.rdbuf(originalCout);
    }
    
    std::string getOutput() {
        return testOutput.str();
    }
    
    void clearOutput() {
        testOutput.str("");
        testOutput.clear();
    }
    
private:
    std::stringstream testOutput;
    std::streambuf* originalCout;
};

TEST_F(TutorialQuestTest, QuestBasicProperties) {
    auto quest = std::make_unique<MockQuest>("Test Quest");
    
    EXPECT_EQ(quest->getName(), "Test Quest");
    EXPECT_EQ(quest->getDescription(), "Mock quest for testing");
    EXPECT_EQ(quest->getLevel(), 0);
    EXPECT_FALSE(quest->isCompleted());
}

TEST_F(TutorialQuestTest, QuestCompletion) {
    auto quest = std::make_unique<MockQuest>("Test Quest", true);
    
    EXPECT_FALSE(quest->isCompleted());
    quest->start();
    EXPECT_TRUE(quest->isCompleted());
    
    std::string output = getOutput();
    EXPECT_NE(output.find("Quest Completed"), std::string::npos);
}

TEST_F(TutorialQuestTest, QuestProgress) {
    auto quest = std::make_unique<MockQuest>("Progress Test");
    
    clearOutput();
    quest->showProgress();
    
    std::string output = getOutput();
    EXPECT_NE(output.find("Progress Test"), std::string::npos);
    EXPECT_NE(output.find("In Progress"), std::string::npos);
}

TEST_F(TutorialQuestTest, QuestManagerBasicUsage) {
    tutorial::QuestManager manager;
    
    manager.addQuest(std::make_unique<MockQuest>("Quest 1", true));
    manager.addQuest(std::make_unique<MockQuest>("Quest 2", true));
    
    EXPECT_FALSE(manager.allQuestsCompleted());
    
    clearOutput();
    manager.showProgress();
    std::string output = getOutput();
    EXPECT_NE(output.find("Tutorial Progress"), std::string::npos);
    EXPECT_NE(output.find("0/2"), std::string::npos);
}

TEST_F(TutorialQuestTest, QuestManagerProgression) {
    tutorial::QuestManager manager;
    
    manager.addQuest(std::make_unique<MockQuest>("Quest 1", true));
    manager.addQuest(std::make_unique<MockQuest>("Quest 2", true));
    
    // Start first quest
    clearOutput();
    manager.startNextQuest();
    EXPECT_FALSE(manager.allQuestsCompleted());
    
    // Start second quest
    clearOutput();
    manager.startNextQuest();
    EXPECT_TRUE(manager.allQuestsCompleted());
}

TEST_F(TutorialQuestTest, BasicsQuestCreation) {
    auto quest = std::make_unique<tutorial::BasicsQuest>();
    
    EXPECT_EQ(quest->getName(), "C++ Basics");
    EXPECT_EQ(quest->getLevel(), 0);
    EXPECT_FALSE(quest->isCompleted());
}

TEST_F(TutorialQuestTest, MemoryQuestCreation) {
    auto quest = std::make_unique<tutorial::MemoryQuest>();
    
    EXPECT_EQ(quest->getName(), "Memory & RAII");
    EXPECT_EQ(quest->getLevel(), 1);
    EXPECT_FALSE(quest->isCompleted());
}

TEST_F(TutorialQuestTest, TutorialHelperFunctions) {
    // Test header printing
    clearOutput();
    tutorial::TutorialHelper::printHeader("Test Header");
    std::string output = getOutput();
    EXPECT_NE(output.find("Test Header"), std::string::npos);
    
    // Test success message
    clearOutput();
    tutorial::TutorialHelper::printSuccess("Success message");
    output = getOutput();
    EXPECT_NE(output.find("Success message"), std::string::npos);
    EXPECT_NE(output.find("✅"), std::string::npos);
    
    // Test error message
    clearOutput();
    tutorial::TutorialHelper::printError("Error message");
    output = getOutput();
    EXPECT_NE(output.find("Error message"), std::string::npos);
    EXPECT_NE(output.find("❌"), std::string::npos);
    
    // Test code printing
    clearOutput();
    tutorial::TutorialHelper::printCode("int x = 42;");
    output = getOutput();
    EXPECT_NE(output.find("int x = 42;"), std::string::npos);
    EXPECT_NE(output.find("```cpp"), std::string::npos);
}
