#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <functional>

namespace tutorial {

/**
 * @brief Base class for all tutorial quests/levels
 * 
 * This class provides the foundation for the gamified learning system.
 * Each quest represents a specific C++ concept or feature to learn.
 */
class Quest {
public:
    Quest(std::string name, std::string description, int level);
    virtual ~Quest() = default;

    // Non-copyable but movable
    Quest(const Quest&) = delete;
    Quest& operator=(const Quest&) = delete;
    Quest(Quest&&) = default;
    Quest& operator=(Quest&&) = default;

    virtual void start() = 0;
    virtual bool isCompleted() const = 0;
    virtual void showProgress() const;

    const std::string& getName() const { return name_; }
    const std::string& getDescription() const { return description_; }
    int getLevel() const { return level_; }

protected:
    void markCompleted();
    void log(const std::string& message) const;

private:
    std::string name_;
    std::string description_;
    int level_;
    bool completed_ = false;
    std::chrono::time_point<std::chrono::steady_clock> startTime_;
};

/**
 * @brief Manages the progression through tutorial quests
 */
class QuestManager {
public:
    void addQuest(std::unique_ptr<Quest> quest);
    void startNextQuest();
    void showProgress() const;
    bool allQuestsCompleted() const;

private:
    std::vector<std::unique_ptr<Quest>> quests_;
    size_t currentQuest_ = 0;
};

/**
 * @brief Utility class for interactive tutorials
 */
class TutorialHelper {
public:
    static void waitForEnter();
    static bool askYesNo(const std::string& question);
    static void printHeader(const std::string& title);
    static void printSuccess(const std::string& message);
    static void printError(const std::string& message);
    static void printCode(const std::string& code);
};

}  // namespace tutorial
