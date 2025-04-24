#include "test.h"
#include <iostream>
#include <cassert>

using namespace std;

void GameTests::RunAllTests() {
    PrintTestResult("GameObject Methods", TestGameObjectMethods());
    PrintTestResult("Rocket Functionality", TestRocketFunctionality());
    PrintTestResult("Assassin Creation", TestAssassinCreation());
    PrintTestResult("Object Interactions", TestObjectInteractions());
    PrintTestResult("Animation Loading", TestAnimationLoading());
}

void GameTests::PrintTestResult(const string& testName, bool passed) {
    cout << testName << ": " << (passed ? "PASS" : "FAIL") << endl;
}

bool GameTests::TestGameObjectMethods() {
    GameObject testObject(4);

    bool initialColumnCorrect = (testObject.getColumn() == 4);

    testObject.setColumn(7);
    bool setColumnWorks = (testObject.getColumn() == 7);

    testObject.setColumn(0);
    bool minColumnWorks = (testObject.getColumn() == 0);

    testObject.setColumn(9);
    bool maxColumnWorks = (testObject.getColumn() == 9);

    return initialColumnCorrect && setColumnWorks && minColumnWorks && maxColumnWorks;
}

bool GameTests::TestRocketFunctionality() {
    Rocket testRocket;

    bool initiallyInactive = !testRocket.isActive();

    testRocket.fire(5, true);
    bool firingActivatesRocket = testRocket.isActive();
    bool columnIsSet = (testRocket.getColumn() == 5);

    Vector2f initialPos = testRocket.getPosition();

    testRocket.update();
    bool rocketMoves = (testRocket.getPosition().y != initialPos.y);

    testRocket.deactivate();
    bool deactivationWorks = !testRocket.isActive();

    return initiallyInactive && firingActivatesRocket && columnIsSet && rocketMoves && deactivationWorks;
}

bool GameTests::TestAssassinCreation() {
    Assassin redAssassin(3, Color::Red);
    Assassin blueAssassin(8, Color::Blue);

    bool redPositionCorrect = (redAssassin.getColumn() == 3);
    bool bluePositionCorrect = (blueAssassin.getColumn() == 8);

    redAssassin.setColumn(1);
    blueAssassin.setColumn(6);

    bool redColumnChangeWorks = (redAssassin.getColumn() == 1);
    bool blueColumnChangeWorks = (blueAssassin.getColumn() == 6);

    try {
        redAssassin.update();
        blueAssassin.update();
        return redPositionCorrect && bluePositionCorrect && redColumnChangeWorks && blueColumnChangeWorks;
    } catch (...) {
        return false;
    }
}

bool GameTests::TestObjectInteractions() {
    Rocket testRocket;
    Assassin testPlayer(5, sf::Color::Red);

    testRocket.fire(5, false);

    bool columnsMatch = (testRocket.getColumn() == testPlayer.getColumn());

    testPlayer.setColumn(2);
    bool columnsNoLongerMatch = (testRocket.getColumn() != testPlayer.getColumn());

    testRocket.deactivate();
    testPlayer.setColumn(5);
    bool noInteractionWhenInactive = !testRocket.isActive();

    return columnsMatch && columnsNoLongerMatch && noInteractionWhenInactive;
}

bool GameTests::TestAnimationLoading() {
    try {
        Assassin testPlayer(0, sf::Color::Red);

        for (int i = 0; i < 10; i++) {
            testPlayer.update();
        }

        return true;
    } catch (...) {
        return false;
    }
}