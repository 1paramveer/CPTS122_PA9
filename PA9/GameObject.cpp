#include "GameObject.h"

/* 
the main purpose of creating this as a class was to track common columns
this lets me track the position for both blob1 and bolb2
this serves as parent class for both Assassin and Rocket classes
*/

GameObject::GameObject(int startCol) { this->column = startCol; }

int GameObject::getColumn() const {
    return this->column;
}

void GameObject::setColumn(int newCol) {
    this->column = newCol;
}
