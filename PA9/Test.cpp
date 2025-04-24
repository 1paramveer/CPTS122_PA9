#include "test.h"
#include <iostream>
#include <cassert>

void GameTests::RunAllTests() {
    std::cout << "Running Game Unit Tests..." << std::endl;
    PrintTestResult("GameObject Methods", TestGameObjectMethods());
    PrintTestResult("Rocket Functionality", TestRocketFunctionality());
    PrintTestResult("Assassin Creation", TestAssassinCreation());
    PrintTestResult("Object Interactions", TestObjectInteractions());
    PrintTestResult("Animation Loading", TestAnimationLoading());
    std::cout << "All tests completed." << std::endl;
}

void GameTests::PrintTestResult(const std::string& testName, bool passed) {
    std::cout << testName << ": " << (passed ? "PASSED" : "FAILED") << std::endl;
}

bool GameTests::TestGameObjectMethods() {
    // Test GameObject's public methods
    GameObject testObject(4);

    // Test initial state
    bool initialColumnCorrect = (testObject.getColumn() == 4);

    // Test column setter
    testObject.setColumn(7);
    bool setColumnWorks = (testObject.getColumn() == 7);

    // Test column bounds (if there were any bounds checking)
    testObject.setColumn(0);
    bool minColumnWorks = (testObject.getColumn() == 0);

    testObject.setColumn(9);
    bool maxColumnWorks = (testObject.getColumn() == 9);

    return initialColumnCorrect && setColumnWorks && minColumnWorks && maxColumnWorks;
}

bool GameTests::TestRocketFunctionality() {
    Rocket testRocket;

    // Test initial state
    bool initiallyInactive = !testRocket.isActive();

    // Test firing upward
    testRocket.fire(5, true);
    bool firingActivatesRocket = testRocket.isActive();
    bool columnIsSet = (testRocket.getColumn() == 5);

    // Store initial position
    sf::Vector2f initialPos = testRocket.getPosition();

    // Test update (movement)
    testRocket.update();
    bool rocketMoves = (testRocket.getPosition().y != initialPos.y);

    // Test deactivation
    testRocket.deactivate();
    bool deactivationWorks = !testRocket.isActive();

    return initiallyInactive && firingActivatesRocket && columnIsSet &&
        rocketMoves && deactivationWorks;
}

bool GameTests::TestAssassinCreation() {
    // Test creating assassins with different colors and positions
    Assassin redAssassin(3, sf::Color::Red);
    Assassin blueAssassin(8, sf::Color::Blue);

    // Test initial column positions
    bool redPositionCorrect = (redAssassin.getColumn() == 3);
    bool bluePositionCorrect = (blueAssassin.getColumn() == 8);

    // Test column changes
    redAssassin.setColumn(1);
    blueAssassin.setColumn(6);

    bool redColumnChangeWorks = (redAssassin.getColumn() == 1);
    bool blueColumnChangeWorks = (blueAssassin.getColumn() == 6);

    // Call update (should not crash if animations loaded correctly)
    try {
        redAssassin.update();
        blueAssassin.update();
        return redPositionCorrect && bluePositionCorrect &&
            redColumnChangeWorks && blueColumnChangeWorks;
    }
    catch (...) {
        return false; // Update crashed, likely animation issue
    }
}

bool GameTests::TestObjectInteractions() {
    // Test interactions between rockets and assassins
    Rocket testRocket;
    Assassin testPlayer(5, sf::Color::Red);

    // Fire rocket in same column as player (potential collision)
    testRocket.fire(5, false);

    // Check if column values match (collision scenario)
    bool columnsMatch = (testRocket.getColumn() == testPlayer.getColumn());

    // Move player away (no collision scenario)
    testPlayer.setColumn(2);
    bool columnsNoLongerMatch = (testRocket.getColumn() != testPlayer.getColumn());

    // Test deactivated rocket interaction
    testRocket.deactivate();
    testPlayer.setColumn(5);
    bool noInteractionWhenInactive = !testRocket.isActive();

    return columnsMatch && columnsNoLongerMatch && noInteractionWhenInactive;
}

bool GameTests::TestAnimationLoading() {
    try {
        // Create an assassin which should load animation frames
        Assassin testPlayer(0, sf::Color::Red);

        // Run several update cycles to test animation frame advancement
        for (int i = 0; i < 10; i++) {
            testPlayer.update();
        }

        // If we get here without crashing, animation loading worked
        return true;
    }
    catch (...) {
        // Something went wrong with animation loading/updating
        return false;
    }
}