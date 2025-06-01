#include "tutorial/quest.hpp"
#include <iomanip>

namespace tutorial {

Quest::Quest(std::string name, std::string description, int level)
    : name_(std::move(name)), description_(std::move(description)), level_(level) {
    startTime_ = std::chrono::steady_clock::now();
}

void Quest::showProgress() const {
    std::cout << "📚 Quest: " << name_ << " (Level " << level_ << ")\n";
    std::cout << "   " << description_ << "\n";
    std::cout << "   Status: " << (completed_ ? "✅ Completed" : "🔄 In Progress") << "\n";
    
    if (!completed_) {
        auto now = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - startTime_);
        std::cout << "   Time spent: " << duration.count() << " seconds\n";
    }
    std::cout << "\n";
}

void Quest::markCompleted() {
    completed_ = true;
    auto endTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime_);
    
    std::cout << "🎉 Quest Completed: " << name_ << " in " << duration.count() << " seconds!\n";
    std::cout << "   You've leveled up your C++ skills! 🚀\n\n";
}

void Quest::log(const std::string& message) const {
    std::cout << "[" << name_ << "] " << message << "\n";
}

void QuestManager::addQuest(std::unique_ptr<Quest> quest) {
    quests_.push_back(std::move(quest));
}

void QuestManager::startNextQuest() {
    if (currentQuest_ < quests_.size()) {
        auto& quest = quests_[currentQuest_];
        TutorialHelper::printHeader("Starting " + quest->getName());
        quest->start();
        
        if (quest->isCompleted()) {
            currentQuest_++;
        }
    }
}

void QuestManager::showProgress() const {
    std::cout << "🎮 Tutorial Progress:\n";
    std::cout << "==================\n\n";
    
    for (size_t i = 0; i < quests_.size(); ++i) {
        std::cout << (i == currentQuest_ ? "➤ " : "  ");
        quests_[i]->showProgress();
    }
    
    double progress = static_cast<double>(currentQuest_) / quests_.size() * 100.0;
    std::cout << "Overall Progress: " << std::fixed << std::setprecision(1) 
              << progress << "% (" << currentQuest_ << "/" << quests_.size() << ")\n\n";
}

bool QuestManager::allQuestsCompleted() const {
    return currentQuest_ >= quests_.size();
}

void TutorialHelper::waitForEnter() {
    std::cout << "Press Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

bool TutorialHelper::askYesNo(const std::string& question) {
    std::cout << question << " (y/n): ";
    std::string response;
    std::getline(std::cin, response);
    return !response.empty() && (response[0] == 'y' || response[0] == 'Y');
}

void TutorialHelper::printHeader(const std::string& title) {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "🎯 " << title << "\n";
    std::cout << std::string(60, '=') << "\n\n";
}

void TutorialHelper::printSuccess(const std::string& message) {
    std::cout << "✅ " << message << "\n";
}

void TutorialHelper::printError(const std::string& message) {
    std::cout << "❌ " << message << "\n";
}

void TutorialHelper::printCode(const std::string& code) {
    std::cout << "```cpp\n" << code << "\n```\n\n";
}

}  // namespace tutorial
