#include "spring.hpp"

#include "../RSDL/rsdl.hpp"
#include "../consts.hpp"

GameObject::CollisionType Spring::collideType_ = GameObject::CollisionType::spring;

void Spring::update(unsigned deltaTime, Window* win) {}

void Spring::draw(Window* win, const PointF& offset) const {
    win->draw_img(sprite::GAMETILES_FILE,
                  Rectangle(box_.x + offset.x, box_.y + offset.y, box_.w, box_.h),
                  sprite::item[currSprite_]);
}

GameObject::CollisionType Spring::collide(GameObject* col, Window* win) {
    if (state_ == State::base) {
        if (col != nullptr) {
            state_ = State::sprung;
            currSprite_ = sprite::Item::SPRUNG;
            box_.y -= sprite::item[sprite::Item::SPRUNG].h - sprite::item[sprite::Item::SPRING].h;
            box_.w = sprite::item[currSprite_].w;
            box_.h = sprite::item[currSprite_].h;
            win->play_sound_effect(consts::SPRING_JUMP_SOUND);
        }
        return collideType_;
    }
    else return CollisionType::none;
}