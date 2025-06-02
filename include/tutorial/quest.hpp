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
    /**
     * @brief Constructor for the Quest.
     * @param name The name of the quest.
     * @param description A short description of the quest.
     * @param level The difficulty level of the quest.
     */
    Quest(std::string name, std::string description, int level);
    virtual ~Quest() = default;

    // Non-copyable but movable
    Quest(const Quest&) = delete;
    Quest& operator=(const Quest&) = delete;
    Quest(Quest&&) = default;
    Quest& operator=(Quest&&) = default;

    /**
     * @brief Starts the quest. Pure virtual function to be implemented by derived classes.
     */
    virtual void start() = 0;

    /**
     * @brief Checks if the quest has been completed. Pure virtual function.
     * @return True if the quest is completed, false otherwise.
     */
    virtual bool isCompleted() const = 0;

    /**
     * @brief Displays the current progress of the quest.
     */
    virtual void showProgress() const;

    /**
     * @brief Gets the name of the quest.
     * @return The name of the quest.
     */
    const std::string& getName() const { return name_; }

    /**
     * @brief Gets the description of the quest.
     * @return The description of the quest.
     */
    const std::string& getDescription() const { return description_; }

    /**
     * @brief Gets the difficulty level of the quest.
     * @return The difficulty level.
     */
    int getLevel() const { return level_; }

protected:
    /**
     * @brief Marks the quest as completed.
     */
    void markCompleted();

    /**
     * @brief Logs a message related to the quest progress.
     * @param message The message to log.
     */
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
    /**
     * @brief Adds a new quest to the manager.
     * @param quest A unique pointer to the quest to be added.
     */
    void addQuest(std::unique_ptr<Quest> quest);

    /**
     * @brief Starts the next available quest. If all quests are completed, it notes that.
     */
    void startNextQuest();

    /**
     * @brief Shows the progress of the current quest or overall tutorial progress.
     */
    void showProgress() const;

    /**
     * @brief Checks if all registered quests have been completed.
     * @return True if all quests are completed, false otherwise.
     */
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
    /**
     * @brief Pauses execution and waits for the user to press Enter.
     */
    static void waitForEnter();

    /**
     * @brief Asks a yes/no question to the user.
     * @param question The question to ask the user.
     * @return True if the user answers yes, false otherwise.
     */
    static bool askYesNo(const std::string& question);

    /**
     * @brief Prints a formatted header to the console.
     * @param title The title text for the header.
     */
    static void printHeader(const std::string& title);

    /**
     * @brief Prints a success message to the console.
     * @param message The success message to print.
     */
    static void printSuccess(const std::string& message);

    /**
     * @brief Prints an error message to the console.
     * @param message The error message to print.
     */
    static void printError(const std::string& message);

    /**
     * @brief Prints a block of code, typically for examples.
     * @param code The code string to print.
     */
    static void printCode(const std::string& code);
};

}  // namespace tutorial
