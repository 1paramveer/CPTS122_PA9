#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>

using namespace std;
using namespace sf;

Game::Game() :
    /* Initializes the main display */
    window(VideoMode(800, 800), "Assassin's Rebellion"),
    player1(0, Color::Red),
    player2(0, Color::Blue),
    state(GameState::MainMenu),
    gamePhase(GamePhase::Normal),
    countdownValue(3),
    deathAnimationTimer(0),
    blinkCount(0),
    blinkVisible(true),
    deadPlayer(0)
{

    /* we had to initialize a timer here to track the blob animation */
    srand(static_cast<unsigned int>(time(nullptr)));
    window.setVerticalSyncEnabled(true);

    /* font */
    font.loadFromFile("../Assets/Fonts/Akira.otf");
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(Color::White);

    mainMenuText.setFont(font);
    mainMenuText.setCharacterSize(32);
    mainMenuText.setFillColor(Color::White);
    mainMenuText.setString("Blobs's Rebellion\n\n1. Play Game\n2. Instructions\n3. Exit");
    mainMenuText.setPosition(200, 200);

    exitScreenText.setFont(font);
    exitScreenText.setCharacterSize(32);
    exitScreenText.setFillColor(Color::White);

    countdownText.setFont(font);
    countdownText.setCharacterSize(72);
    countdownText.setFillColor(Color::White);
    countdownText.setPosition(375, 350);

    /* background */
    backgroundTexture.loadFromFile("../Assets/Backgrounds/gameplay-background.png");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(800.0f / 600.0f, 800.0f / 600.0f);

    /* sound */
    backgroundMusic.openFromFile("../Assets/Sounds/bgm.mp3");
    backgroundMusic.setLoop(true); 
    backgroundMusic.setVolume(25);
    backgroundMusic.play();

    movementSoundBuffer.loadFromFile("../Assets/Sounds/blob-move.mp3");
    movementSound.setBuffer(movementSoundBuffer);
    movementSound.setVolume(35);

    whooshSoundBuffer.loadFromFile("../Assets/Sounds/whoosh.mp3");
    whooshSound.setBuffer(whooshSoundBuffer);
    whooshSound.setVolume(50);

    resetPositions();
}

/* 
    Randomizes player positions, deletes active rockets ensuring that if played again
    the rockets would not be there, resets the score
*/
void Game::resetPositions() {
    do {
        this->player1.setColumn(rand() % 10);
        this->player2.setColumn(rand() % 10);
    } while (this->player1.getColumn() == this->player2.getColumn());

    this->p1AttemptedKill = false;
    this->p2AttemptedKill = false;
    this->player1Rocket.deactivate();
    this->player2Rocket.deactivate();
}

/**
 * Run Game Loop
 *
 * Main game loop that handles events, updates game logic, and renders.
 * Manages timing, input processing, and frame rendering based on game state.
 */
void Game::run() {
    Clock clock;
    float moveDelay = 0.2f;
    float lastMoveTime = 0;
    float dt = 0;

    while (window.isOpen()) {
        dt = clock.restart().asSeconds();

        float currentTime = gameplayClock.getElapsedTime().asSeconds();
        Event event;

        while (window.pollEvent(event)) {

            if (event.type == Event::Closed) {
                window.close();
            }

            switch (state) {

            case GameState::MainMenu:
                handleMainMenuInput(event);
                break;

            case GameState::Playing:
                if (event.type == Event::KeyPressed) {
                    if (event.key.code == Keyboard::Escape) {
                        state = GameState::ExitScreen;
                    } else if (gamePhase == GamePhase::Normal && currentTime - lastMoveTime > moveDelay) {
                        lastMoveTime = currentTime;

                        /*
                           Player 1 movement - Bottom blob - arrow keys
                         */
                        if (event.key.code == Keyboard::Left) {
                            movementSound.play();

                            int newColumn = player1.getColumn() - 1; // moves left

                            if (newColumn >= 0) {
                                player1.setColumn(newColumn);
                            }
                        } else if (event.key.code == Keyboard::Right) {
                            movementSound.play();

                            int newColumn = player1.getColumn() + 1; // moves right

                            if (newColumn <= 9) {
                                player1.setColumn(newColumn);
                            }
                        }

                        /**
                          Player 2 movement - Top blob - WASD keys
                         */
                        if (event.key.code == Keyboard::A) {
                            movementSound.play();

                            int newColumn = player2.getColumn() - 1;

                            if (newColumn >= 0) {
                                player2.setColumn(newColumn);
                            }
                        } else if (event.key.code == Keyboard::D) {
                            movementSound.play();

                            int newColumn = player2.getColumn() + 1;
                            if (newColumn <= 9) {
                                player2.setColumn(newColumn);
                            }
                        }

                        /*
                          firing rockets
                          Player 1 uses Enter, Player 2 uses Space
                         */
                        if (event.key.code == Keyboard::Space) {
                            whooshSound.play();

                            p2AttemptedKill = true;
                            checkKill(2);
                        } else if (event.key.code == Keyboard::Enter) {
                            whooshSound.play();

                            p1AttemptedKill = true;
                            checkKill(1);
                        }
                    }
                }
                break;

            case GameState::ExitScreen:
                handleExitScreenInput(event);
                break;
            }
        }

        updateGameLogic(dt);
        window.clear(Color::Black);

        switch (state) {
        case GameState::MainMenu:
            renderMainMenu();
            break;
        case GameState::Playing:
            renderGame();
            break;
        case GameState::ExitScreen:
            renderExitScreen();
            break;
        }

        window.display();
    }
}

/* 
    This handles the core logic for the enire game, including 
    charachter movement, 
    rocket movement, 
    animation,
    scoreboard,
    transition ( Lifecycle of the entire game) 
*/
void Game::updateGameLogic(float dt) {
    if (state != GameState::Playing) return;

    player1.update();
    player2.update();
    player1Rocket.update();
    player2Rocket.update();

    /*
      Rocket collision detection
      If two rockets are fired at the same time, they both get deactivated 
     */
    if (player1Rocket.isActive() && player2Rocket.isActive() &&
        player1Rocket.getColumn() == player2Rocket.getColumn()) {
        if (player1Rocket.getPosition().y <= player2Rocket.getPosition().y) {
            player1Rocket.deactivate();
            player2Rocket.deactivate();
        }
    }

    /**
     * Player collision detection
     * Checks if player is hit by opponent's rocket
     */
    if (player1Rocket.isActive() && player1Rocket.getColumn() == player2.getColumn() && player1Rocket.getPosition().y <= 100.0f) {
        
        deadPlayer = 2;
        player1Rocket.deactivate();
        gamePhase = GamePhase::DeathAnimation; // just a blink animation
        deathAnimationTimer = 0;
        blinkCount = 0;
        blinkVisible = true;
    }
    if (player2Rocket.isActive() && player2Rocket.getColumn() == player1.getColumn() && player2Rocket.getPosition().y >= 700.0f) {

        deadPlayer = 1;
        player2Rocket.deactivate();
        gamePhase = GamePhase::DeathAnimation; // just a blink animation
        deathAnimationTimer = 0;
        blinkCount = 0;
        blinkVisible = true;
    }

    /* handles gamephase */
    switch (gamePhase) {

    case GamePhase::Normal:
        break;

    case GamePhase::RocketFired:
        if (!player1Rocket.isActive() && !player2Rocket.isActive()) {
            if (deadPlayer == 0) {
                gamePhase = GamePhase::Normal;
            }
        }
        break;

    case GamePhase::DeathAnimation:
        deathAnimationTimer += dt; 

        if (deathAnimationTimer > 0.15f) {
            deathAnimationTimer = 0;
            blinkVisible = !blinkVisible;
            blinkCount++;

            if (blinkCount >= 6) {
                if (deadPlayer == 1) p2Score++;
                else p1Score++;

                deadPlayer = 0;
                if (p1Score >= 3 || p2Score >= 3) {
                    state = GameState::ExitScreen;
                }
                else {
                    gamePhase = GamePhase::Countdown;
                    countdownValue = 3;
                    deathAnimationTimer = 0;
                }
            }
        }
        break;

    case GamePhase::Countdown:
        deathAnimationTimer += dt;

        if (deathAnimationTimer > 1.0f) {
            deathAnimationTimer = 0;
            countdownValue--;

            if (countdownValue <= 0) {
                gamePhase = GamePhase::Normal;
                resetPositions();
            }
        }

        break;
    }
}

void Game::renderMainMenu() {
    window.draw(backgroundSprite);

    if (mainMenuText.getString() == "Instructions") {
        renderInstructions();
    } else {
        window.draw(mainMenuText);
    }
}

/* Instructions */
void Game::renderInstructions() {
    Text instructionsText;
    instructionsText.setFont(font);
    instructionsText.setCharacterSize(24);
    instructionsText.setFillColor(Color::White);
    instructionsText.setLineSpacing(1.2f);

    string instructions =
        "Instructions !\n"
        "2v2 Game, first to hit 3 rocket wins\n\n"
        "PLAYER 1 RED - BOTTOM\n"
        "Movement: LEFT/RIGHT Arrow Keys\n"
        "Fire: ENTER\n\n"
        "PLAYER 2 BLUE - TOP\n"
        "Movement: A/D Keys\n"
        "Fire: SPACE\n\n"
        "\n"
        "- Rockets show direction\n"
        "- Colliding rockets cancel\n"
        "- Align column to hit\n"
        "Press ESC to return";

    instructionsText.setString(instructions);
    instructionsText.setPosition(50, 100);
    window.draw(instructionsText);
}

/* Renders the game UI */
void Game::renderGame() {
    window.draw(backgroundSprite);

    if (gamePhase != GamePhase::DeathAnimation || deadPlayer != 1 || blinkVisible) {
        player1.draw(window);
    }
    if (gamePhase != GamePhase::DeathAnimation || deadPlayer != 2 || blinkVisible) {
        player2.draw(window);
    }

    player1Rocket.draw(window);
    player2Rocket.draw(window);

    updateScoreDisplay();
    window.draw(scoreText);

    if (gamePhase == GamePhase::Countdown) {
        countdownText.setString(to_string(countdownValue));
        window.draw(countdownText);
    }
}

/* Main Menu */
void Game::handleMainMenuInput(Event& event) {
    if (event.type == Event::KeyPressed) {
        if (event.key.code == Keyboard::Num1) {
            state = GameState::Playing;
            resetGame();
        } else if (event.key.code == Keyboard::Num2) {
            mainMenuText.setString("Instructions");
        } else if (event.key.code == Keyboard::Num3) {
            window.close();
        } else if (event.key.code == Keyboard::Escape) {
            if (mainMenuText.getString() == "Instructions") {
                mainMenuText.setString("Blobs Assassin's Rebellion\n\n1. Play Game\n2. Instructions\n3. Exit");
            }
        }
    }
}

/* Exit screen */
void Game::renderExitScreen() {
    window.draw(backgroundSprite);
    string result = "Game Over!\n";
    if (p1Score >= 3 && p2Score >= 3) {
        result += "It's a Tie!\n";
    }
    else if (p1Score >= 3) {
        result += "You Win!\n";
    }
    else if (p2Score >= 3) {
        result += "Opponent Wins!\n";
    }
    else {
        result += "Game Ended Early\n";
    }

    result += "You (Red): " + to_string(p1Score) + "\n";
    result += "Opponent (Green): " + to_string(p2Score) + "\n\n";
    result += "1. Main Menu\n2. Exit";

    exitScreenText.setString(result);
    exitScreenText.setPosition(200, 200);
    window.draw(exitScreenText);
}

/* Exit game screen */
void Game::handleExitScreenInput(Event& event) {
    if (event.type == Event::KeyPressed) {
        if (event.key.code == Keyboard::Num1) {
            state = GameState::MainMenu;
            mainMenuText.setString("Blobs Assassin's Rebellion\n\n1. Play Game\n2. Instructions\n3. Exit");
            resetGame();
        }
        else if (event.key.code == Keyboard::Num2) {
            window.close();
        }
    }
}

/* zconfirms kill */
void Game::checkKill(int attacker) {
    if (gamePhase != GamePhase::Normal) return;

    if (attacker == 1) {
        player1Rocket.fire(player1.getColumn(), true);
    }
    else {
        player2Rocket.fire(player2.getColumn(), false);
    }
    gamePhase = GamePhase::RocketFired;
}

void Game::resetGame() {
    p1Score = 0;
    p2Score = 0;
    gamePhase = GamePhase::Normal;
    resetPositions();
}

void Game::updateScoreDisplay() {
    string text = "You (Red): " + to_string(p1Score) + "\n" + "Opponent (Green): " + to_string(p2Score);

    scoreText.setString(text);
    scoreText.setPosition(10, 10);
    scoreText.setFillColor(Color::White);
}