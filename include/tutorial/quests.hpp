#pragma once

#include "tutorial/quest.hpp"

namespace tutorial {

/**
 * @brief Level 0: Basic C++ syntax and fundamentals
 */
class BasicsQuest : public Quest {
public:
    BasicsQuest();
    void start() override;
    bool isCompleted() const override;

private:
    void demonstrateTypes();
    void demonstrateControlFlow();
    void demonstrateFunctions();
    bool completed_ = false;
};

/**
 * @brief Level 1: Memory management and RAII
 */
class MemoryQuest : public Quest {
public:
    MemoryQuest();
    void start() override;
    bool isCompleted() const override;

private:
    void demonstrateStackVsHeap();
    void demonstrateRAII();
    void demonstrateSmartPointers();
    void demonstrateMoveSemantics();
    bool completed_ = false;
};

/**
 * @brief Level 2: Object-oriented programming
 */
class OOPQuest : public Quest {
public:
    OOPQuest();
    void start() override;
    bool isCompleted() const override;

private:
    void demonstrateClasses();
    void demonstrateInheritance();
    void demonstratePolymorphism();
    void demonstrateRuleOfFive();
    bool completed_ = false;
};

/**
 * @brief Level 3: Templates and generic programming
 */
class TemplatesQuest : public Quest {
public:
    TemplatesQuest();
    void start() override;
    bool isCompleted() const override;

private:
    void demonstrateFunctionTemplates();
    void demonstrateClassTemplates();
    void demonstrateVariadicTemplates();
    void demonstrateTypeTraits();
    void demonstrateSTLAlgorithms();
    bool completed_ = false;
};

/**
 * @brief Level 4: STL containers and algorithms
 */
class STLQuest : public Quest {
public:
    STLQuest();
    void start() override;
    bool isCompleted() const override;

private:
    void demonstrateSequenceContainers();
    void demonstrateAssociativeContainers();
    void demonstrateContainerAdaptors();
    void demonstrateIterators();
    void demonstrateAlgorithms();
    bool completed_ = false;
};

/**
 * @brief Level 5: Concurrency and parallel programming
 */
class ConcurrencyQuest : public Quest {
public:
    ConcurrencyQuest();
    void start() override;
    bool isCompleted() const override;

private:
    void demonstrateBasicThreads();
    void demonstrateSynchronization();
    void demonstrateAsyncProgramming();
    void demonstrateAtomicOperations();
    void demonstrateParallelAlgorithms();
    bool completed_ = false;
};

}  // namespace tutorial
