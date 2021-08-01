#include "enemy_normal.hpp"

#include "../RSDL/rsdl.hpp"
#include "../spritesheet.hpp"

GameObject::CollisionType EnemyNormal::collideType_ = GameObject::CollisionType::enemyNormal;

void EnemyNormal::update(unsigned deltaTime, Window* win) {
    if (state_ == State::base) {
        box_.y += ((hoverTimer_ < 500) ? 1 : -1) * 0.014 * deltaTime;
        hoverTimer_ += deltaTime;
        if (hoverTimer_ > 1000) hoverTimer_ = 0;
    }
    else if (state_ == State::dying) {
        if (dieAnimationTimer_ > 400) state_ = State::vanished;
        dieAnimationTimer_ += deltaTime;
        box_.y += 0.2 * deltaTime;
    }
}

void EnemyNormal::draw(Window* win, const PointF& offset) const {
    if (state_ != State::vanished) {
        win->draw_img(sprite::GAMETILES_FILE,
                      Rectangle(box_.x + offset.x, box_.y + offset.y, box_.w, box_.h),
                      sprite::enemy[sprite::Enemy::NORM]);
    }
}

GameObject::CollisionType EnemyNormal::collide(GameObject* col, Window* win) {
    if (state_ == State::base) {
        if (col != nullptr) {
            state_ = State::dying;
        }
        return collideType_;
    }
    else return CollisionType::none;
}