#pragma once

#include "GameObject.h"
#include "Rocket.h"
#include "Assassin.h"
#include <string>

using namespace std;
using namespace sf;

class GameTests {
public:
    static void RunAllTests();
    static void PrintTestResult(const string& testName, bool passed);

    static bool TestGameObjectMethods();
    static bool TestRocketFunctionality();
    static bool TestAssassinCreation();
    static bool TestObjectInteractions();
    static bool TestAnimationLoading();
};
