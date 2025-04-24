#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

class Animation {
private:
    vector<Texture*> frames;   // points to the sequence of images 
    vector<Sprite> sprites;    // SFMl sprite builder
    float frameDuration;      
    float elapsedTime;         
    size_t currentFrame;       

public:
    Animation(const vector<Texture*>& frameTextures, float totalDuration) {
        this->frames = frameTextures;
        this->frameDuration = totalDuration / frameTextures.size();
        this->elapsedTime = 0.5f;
        this->currentFrame = 0;

        updateSpriteReferences();
    }

    /* turns images into sprite */
    void updateSpriteReferences() {
        sprites.clear();
        for (Texture* tex : frames)  
            sprites.emplace_back(*tex);

    }

    /* updates frames based on elapsed time */
    void update(float dt) {
        elapsedTime += dt;
        if (elapsedTime >= frameDuration) {
            currentFrame = (currentFrame + 1) % frames.size();
            elapsedTime = 0.f;
        }
    }

    /* returns playing sprite */
    Sprite& getCurrentSprite() { return sprites[currentFrame]; }

    /* resets animation, sets frame to 0 */
    void reset() {
        this->currentFrame = 0;
        this->elapsedTime = 0.f;
    }
};
