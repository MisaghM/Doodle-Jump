#include "doodle.hpp"

#include "RSDL/rsdl.hpp"
#include "input_manager.hpp"

GameObject::CollisionType Doodle::collideType_ = CollisionType::none;

void Doodle::draw(Window* win, const PointF& offset) const {
    win->draw_img(sprite::DOODLE_FILE,
                  Rectangle(box_.x + offset.x, box_.y + offset.y, box_.w, box_.h),
                  sprite::doodle[spriteState_]);
}

void Doodle::update(unsigned deltaTime, Window* win) {
    box_.y -= vy_ * deltaTime;
    vy_ -= consts::G * deltaTime;
    box_.x += vx_ * deltaTime;

    if (box_.x > win->get_width()) box_.x = 0;
    else if (box_.x + box_.w < 0)
        box_.x = win->get_width();

    if (state_ == State::base) {
        setSpriteState();
        setHitbox();
    }

    if (!isDead() && isOutOfScreenBottom(win)) {
        die(win);
    }
}

void Doodle::updateInputs(InputManager* inputMan) {
    if (state_ != State::base) return;

    int direction = inputMan->isKeyPressed(InputKeys::right) - inputMan->isKeyPressed(InputKeys::left);

    if (direction > 0) {
        spriteState_ = (vy_ > 0.5 * consts::DOODLE_VY) ? charState::RIGHTJUMP : charState::RIGHT;
        vx_ = consts::DOODLE_VX;
    }
    else if (direction < 0) {
        spriteState_ = (vy_ > 0.5 * consts::DOODLE_VY) ? charState::LEFTJUMP : charState::LEFT;
        vx_ = -consts::DOODLE_VX;
    }
    else vx_ = 0;
}

GameObject::CollisionType Doodle::collide(GameObject* col, Window* win) {
    if (state_ == State::base) {
        switch (col->collide(nullptr, win)) {
        case CollisionType::pNormal:
        case CollisionType::pMovable:
            if (hasHitFromAbove(col)) {
                vy_ = consts::DOODLE_VY;
                box_.y = col->getY() - col->getHeight() - box_.h;
                win->play_sound_effect(consts::DOODLE_JUMP_SOUND);
            }
            break;
        case CollisionType::spring:
            if (hasHitFromAbove(col)) {
                col->collide(this, win);
                vy_ = consts::DOODLE_VY_SPRING;
            }
            break;
        case CollisionType::pBreakable:
            if (hasHitFromAbove(col)) {
                col->collide(this, win);
            }
            break;
        case CollisionType::enemyNormal:
            if (hasHitFromAbove(col)) {
                col->collide(this, win);
                vy_ = consts::DOODLE_VY;
                win->play_sound_effect(consts::DOODLE_JUMP_ON_ENEMY_SOUND);
            }
            else {
                state_ = State::hit;
                if (vy_ > 0) {
                    vy_ = -0.04 * consts::DOODLE_VY;
                }
                win->play_sound_effect(consts::DOODLE_HIT_BY_ENEMY_SOUND);
            }
            break;
        default: break;
        }
    }
    return collideType_;
}

bool Doodle::isOutOfScreenBottom(const Window* win) const {
    return (box_.y + box_.h * 0.9 >= win->get_height());
}

void Doodle::setSpriteState() {
    if (spriteState_ == charState::RIGHT || spriteState_ == charState::RIGHTJUMP) {
        spriteState_ = (vy_ > 0.5 * consts::DOODLE_VY) ? charState::RIGHTJUMP : charState::RIGHT;
    }
    else {
        spriteState_ = (vy_ > 0.5 * consts::DOODLE_VY) ? charState::LEFTJUMP : charState::LEFT;
    }
}

void Doodle::setHitbox() {
    //set the hitbox so that the nose is not part of it
    if (spriteState_ == charState::RIGHT || spriteState_ == charState::RIGHTJUMP) {
        hitBox_.x = 0;
        hitBox_.w = 0.7 * box_.w;
    }
    else {
        hitBox_.x = 0.3 * box_.w;
        hitBox_.w = 0.7 * box_.w;
    }
}

void Doodle::die(Window* win) {
    win->play_sound_effect(consts::DOODLE_DEATH_SOUND);
    state_ = State::dead;
}

bool Doodle::hasHitFromAbove(const GameObject* collided) const {
    return (vy_ <= 0 &&
            box_.y + hitBox_.y + hitBox_.h - collided->getY() - collided->getHitboxDeltaY() <= 20);
}

bool Doodle::isDead() const { return state_ == State::dead; }