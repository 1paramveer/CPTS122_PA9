# Blob Assassin's Rebellion

## Team Members
* Vedant Naidu
* Madison Suxus Dennis
* Paramweer Singh
* Rajendriya Das

## Demo Link
[Gameplay](https://youtu.be/DziCz2_v8sM?si=V2iDwNqYRRvjxPD-)
[Detailed Explanation](https://youtu.be/qT4tzCQUKKY?si=B7_TiMACNlMiqMNb)

## Game Overview
**Blob Assassin's Rebellion** is a fast-paced, two-player arcade shooter developed in C++ using the SFML graphics library. Inspired by retro couch co-op titles, the game pits two players—Red vs. Blue—in a direct competitive showdown. Each player controls a character (a blob) on opposite ends of the screen, with the objective of strategically moving and firing rockets to eliminate the opponent. The first to land **three successful hits** wins.

## Controls
### Player 1: Red Blob (Bottom of the screen)
* Move: Left and right arrow keys
* Fire: ENTER

### Player 2: Green Blob (Top of the screen)
* Move: a and d for left and right
* Fire: SPACE

### Other Controls
* Pause / Main Menu: ESC

## Gameplay Mechanics
* Both players can move horizontally across **10 fixed columns**
* Players fire rockets vertically toward the opposing player
* If a rocket hits the opponent, they **lose one point**
* The **first player to get 3 hits** wins the match
* The game includes a **countdown before each match** and a **summary screen** at the end

## Key Features
* Developed using **SFML** for smooth 2D graphics and animations
* Full **Object-Oriented Programming (OOP)** structure with inheritance:
  * Base class: GameObject
  * Derived classes: Assassin, Rocket
* Modular design with **3+ C++ source files** and **2+ header files**
* Integrated **main menu**, **instructions screen**, and **endgame logic**
* **Dynamic game loop** and state transitions (pause, restart, win screen)
* **At least 5 test cases** to validate core gameplay features and object interactions
* Designed for **local multiplayer (couch-style)** with simultaneous player input

## Technical Notes
* Built and tested in **Visual Studio**
* Uses **SFML** for rendering, event handling, and resource management
* All assets (sprites, fonts, sounds) must be placed in their **correct relative paths** for proper execution
* No debug folders are included in the final project submission

## Setup Instructions
1. Ensure SFML is properly linked in your Visual Studio environment
2. Clone or download the project repository
3. Place assets in the required folders as described in README_Assets.txt
4. Compile and run main.cpp from your Visual Studio IDE

## Final Notes
We hope you enjoy playing **Blob Assassin's Rebellion** as much as we enjoyed building it. This game was created as part of the CptS 122 curriculum to demonstrate mastery in C++ game development, object-oriented design, and creative collaboration.

Have fun, and may the best assassin win!

## Team Sections and TA Information
* Vedant Naidu - Section 3, Kyle Parker 11830467
* Madison Suxus Dennis - Section 12, Dylan S. 11905887
* Paramveer Singh - Section 12, Dylan S. 011912039
* Rajendriya Das - Section 5, Jaehong Lee 11839681