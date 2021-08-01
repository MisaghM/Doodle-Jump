#include "game_object.hpp"

#include <stdexcept>

GameObject::GameObject(const RectangleF& box, const RectangleF& hitBox)
    : box_(box),
      hitBox_(hitBox) {
    if (box.w <= 0 || box.h <= 0 || hitBox.w < 0 || hitBox_.h < 0) {
        throw std::invalid_argument("Invalid width/height for game object.");
    }
}
GameObject::GameObject(const RectangleF& box)
    : GameObject(box, RectangleF(0, 0, box.w, box.h)) {}

GameObject::~GameObject() {}

void GameObject::translateY(float deltaY) { box_.y += deltaY; }

int GameObject::getX() const { return box_.x; }
int GameObject::getY() const { return box_.y; }
int GameObject::getWidth() const { return box_.w; }
int GameObject::getHeight() const { return box_.h; }

int GameObject::getHitboxDeltaX() const { return hitBox_.x; }
int GameObject::getHitboxDeltaY() const { return hitBox_.y; }
int GameObject::getHitboxWidth() const { return hitBox_.w; }
int GameObject::getHitboxHeight() const { return hitBox_.h; }