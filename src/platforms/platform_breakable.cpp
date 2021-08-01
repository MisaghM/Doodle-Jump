#include "platform_breakable.hpp"

#include "../RSDL/rsdl.hpp"
#include "../consts.hpp"

GameObject::CollisionType PlatformBreakable::collideType_ = GameObject::CollisionType::pBreakable;

void PlatformBreakable::update(unsigned deltaTime, Window* win) {
    if (state_ == State::broke) {
        breakAnimationTimer_ += deltaTime;
        if (breakAnimationTimer_ >= 650) {
            state_ = State::vanished;
        }
        else if (breakAnimationTimer_ > 120) {
            currSprite_ = sprite::Platform::BREAKABLE_B3;
        }
        else if (breakAnimationTimer_ > 80) {
            currSprite_ = sprite::Platform::BREAKABLE_B2;
        }
        else if (breakAnimationTimer_ > 40) {
            currSprite_ = sprite::Platform::BREAKABLE_B1;
        }
        box_.w = sprite::platform[currSprite_].w;
        box_.h = sprite::platform[currSprite_].h;
        box_.y += 0.4 * deltaTime;
    }
}

void PlatformBreakable::draw(Window* win, const PointF& offset) const {
    if (state_ != State::vanished) {
        win->draw_img(sprite::GAMETILES_FILE,
                      Rectangle(box_.x + offset.x, box_.y + offset.y, box_.w, box_.h),
                      sprite::platform[currSprite_]);
    }
}

GameObject::CollisionType PlatformBreakable::collide(GameObject* col, Window* win) {
    if (state_ == State::base) {
        if (col != nullptr) {
            state_ = State::broke;
            win->play_sound_effect(consts::PLAT_BREAK_SOUND);
        }
        return collideType_;
    }
    else return CollisionType::none;
}