#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class GameObject {
protected:
    int column;
    Vector2f position;

public:
    GameObject(int startCol);

    virtual void update() {}
    virtual void draw(RenderWindow& window) {}

    int getColumn() const;
    void setColumn(int newCol);
};