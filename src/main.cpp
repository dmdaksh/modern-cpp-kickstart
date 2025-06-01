#include "tutorial/quest.hpp"
#include "tutorial/quests.hpp"
#include <iostream>
#include <memory>

void printWelcome() {
    std::cout << R"(
🚀 ========================================== 🚀
   Welcome to Modern C++ Tutorial & Starter!
🚀 ========================================== 🚀

This is a gamified journey through modern C++ features.
Complete quests to level up your C++ skills!

Features you'll master:
• 🎯 Modern C++ (C++11 to C++23)
• 🧠 Memory management & RAII
• 🏗️  Object-oriented programming
• 🔮 Templates & generic programming
• 🌊 STL containers & algorithms
• ⚙️  Concurrency & parallel programming

)" << std::endl;
}

void printCongratulations() {
    std::cout << R"(
🏆 =============================================== 🏆
       CONGRATULATIONS! 🎉
🏆 =============================================== 🏆

You've completed the C++ Tutorial!

You've mastered:
✅ Modern C++ syntax and best practices
✅ Memory management with RAII and smart pointers
✅ Object-oriented programming principles
✅ Template programming and generics
✅ STL containers and algorithms
✅ Concurrency and parallel programming

🚀 You're now ready to build amazing C++ applications!

This repository is now ready to be used as a project starter.
Simply remove the tutorial code and keep the core infrastructure.

Happy coding! 🎊
)" << std::endl;
}

int main() {
    try {
        printWelcome();
        
        // Create quest manager
        tutorial::QuestManager questManager;
        
        // Add all quests in order
        questManager.addQuest(std::make_unique<tutorial::BasicsQuest>());
        questManager.addQuest(std::make_unique<tutorial::MemoryQuest>());
        questManager.addQuest(std::make_unique<tutorial::OOPQuest>());
        questManager.addQuest(std::make_unique<tutorial::TemplatesQuest>());
        questManager.addQuest(std::make_unique<tutorial::STLQuest>());
        questManager.addQuest(std::make_unique<tutorial::ConcurrencyQuest>());
        
        // Main tutorial loop
        while (!questManager.allQuestsCompleted()) {
            questManager.showProgress();
            
            if (tutorial::TutorialHelper::askYesNo("Ready to start the next quest?")) {
                questManager.startNextQuest();
            } else {
                std::cout << "Take your time! Run the program again when you're ready.\n";
                break;
            }
        }
        
        if (questManager.allQuestsCompleted()) {
            printCongratulations();
        }
        
    } catch (const std::exception& e) {
        std::cerr << "❌ Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
