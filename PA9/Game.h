#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Assassin.h"
#include "Rocket.h"

using namespace std;
using namespace sf;

class Game {
private:
    enum class GameState { MainMenu, Playing, ExitScreen };
    enum class GamePhase { Normal, RocketFired, DeathAnimation, Countdown };

    GameState state;
    GamePhase gamePhase;
    bool p1AttemptedKill = false;
    bool p2AttemptedKill = false;

    RenderWindow window;
    Assassin player1;
    Assassin player2;
    Rocket player1Rocket;
    Rocket player2Rocket;

    int p1Score = 0;
    int p2Score = 0;
    Font font;
    Text scoreText;
    Text mainMenuText;
    Text exitScreenText;
    Text countdownText;
    Texture backgroundTexture;
    Sprite backgroundSprite;

    Music backgroundMusic;

    SoundBuffer movementSoundBuffer;
    Sound movementSound;
    SoundBuffer whooshSoundBuffer;
    Sound whooshSound;

    Clock gameplayClock;
    float deathAnimationTimer;
    int blinkCount;
    bool blinkVisible;
    int deadPlayer; 
    int countdownValue;

    void resetPositions();
    void checkKill(int attacker);
    void updateScoreDisplay();
    void resetGame();
    void renderMainMenu();
    void renderInstructions();
    void handleMainMenuInput(Event& event);
    void renderExitScreen();
    void handleExitScreenInput(Event& event);
    void updateGameLogic(float dt);
    void renderGame();

public:
    Game();
    void run();
};