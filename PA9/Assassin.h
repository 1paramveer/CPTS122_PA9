#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include "Animation.h"

using namespace std;
using namespace sf;

class Assassin : public GameObject {
private:
    Color color;                          
    vector<Texture> idleTextures;   
    Animation idleAnimation;                
    Animation* currentAnimation;              

public:
    Assassin(int startCol, const Color& c);
    ~Assassin();

    void update() override;
    void draw(RenderWindow& window) override;
};