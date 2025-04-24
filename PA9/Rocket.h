#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

using namespace std;
using namespace sf;

class Rocket : public GameObject {
private:
    Texture textureUp;   
    Texture textureDown; 
    Sprite sprite;
    bool active;
    float speed;
    bool movingDown; 

public:
    Rocket();
    void fire(int column, bool down);
    
    bool isActive() const;
    void deactivate();

    void update() override;
    void draw(RenderWindow& window) override;

    const Vector2f& getPosition() const { return position; }
    int getColumn() const { return column; }
};