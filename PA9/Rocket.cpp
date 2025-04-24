#include "Rocket.h"
#include <iostream>

/* Initializes rockets
loads rocket (59x59px) textures, for both directions 
Did this manually, turned rocket upside down using photo editor 
*/
Rocket::Rocket() : GameObject(0) {
    this->active = false;
    this->speed = 800.0f;
    this->movingDown = true;

    textureUp.loadFromFile("../Assets/rocketUp.png");
    textureDown.loadFromFile("../Assets/rocketDown.png");

    sprite.setOrigin(30.0f, 30.0f);
}

/* Fires rocket 
sets position based on the current x, y positon of blobs
*/
void Rocket::fire(int column, bool down) {
    this->column = column;
    this->movingDown = down;

    if (movingDown) {
        sprite.setTexture(textureUp);
    } else {
        sprite.setTexture(textureDown);
    }

    position.x = 80.f + (column * 64.f); // initial x pos

    if (movingDown) {
        position.y = 700.0f;  // makes rocket go down
    } else {
        position.y = 100.0f;  // nmakes rocket go up
    }

    this->active = true;
}

/* main movement logic */
void Rocket::update() {
    if (!this->active) return; // error check to check about activa

    if (this->movingDown) {
        // makes rocket move up, stops and sets the status to false
        position.y -= speed / 60.0f;
        if (position.y < 0.0f) this->active = false;
    } else {
        // makes rocket move down, stops and sets the status to false
        position.y += speed / 60.0f;
        if (position.y > 800.0f) this->active = false;
    }

    sprite.setPosition(position);
}

/* draws rocket on window based on the status */
void Rocket::draw(sf::RenderWindow& window) {
    if (this->active) window.draw(sprite);
}

bool Rocket::isActive() const {
    return this->active;
}

void Rocket::deactivate() {
    this->active = false;
}