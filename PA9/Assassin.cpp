#include "Assassin.h"
#include <iostream>

Assassin::Assassin(int startCol, const sf::Color& c)
    : GameObject(startCol), color(c),
    idleAnimation({}, 1.0f) // Temporary empty animation
{
    // Determine character name based on color
    std::string characterName = (color == sf::Color::Red) ? "blob1" : "blob2";
    std::string basePath = "../Assets/Sprites/" + characterName + "/idle";

    // Load idle frames
    std::vector<sf::Texture*> idleFrameTextures;
    idleTextures.reserve(8); // Pre-allocate to avoid reallocation

    for (int i = 1; i <= 8; ++i) {
        idleTextures.emplace_back();
        if (!idleTextures.back().loadFromFile(basePath + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load idle frame " << i << " for " << characterName << std::endl;
        }
        else {
            // Only add successfully loaded textures
            idleFrameTextures.push_back(&idleTextures.back());
        }
    }

    // Initialize idle animation with loaded textures
    idleAnimation = Animation(idleFrameTextures, 2.0f);
    idleAnimation.updateSpriteReferences(); // Update references after assignment
    currentAnimation = &idleAnimation;
}

Assassin::~Assassin() {}

void Assassin::update() {
    // Update position (same as before)
    position.x = 80.f + (column * 64.f);
    position.y = (color == sf::Color::Blue) ? 100.f : 700.f;

    // Update animation
    currentAnimation->update(1.0f / 60.0f); // Assume 60 FPS

    // Update sprite position
    sf::Sprite& currentSprite = currentAnimation->getCurrentSprite();
    currentSprite.setPosition(position);
    currentSprite.setScale(3.0f, 3.0f); // Scale to ~64x64 (assuming 32x32 frames)
}

void Assassin::draw(sf::RenderWindow& window) {
    window.draw(currentAnimation->getCurrentSprite());
}