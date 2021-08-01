#include "platform_movable.hpp"

#include "../RSDL/rsdl.hpp"
#include "../spritesheet.hpp"

GameObject::CollisionType PlatformMovable::collideType_ = GameObject::CollisionType::pMovable;

PlatformMovable::PlatformMovable(const RectangleF& box, const RectangleF& hitBox, float vx)
    : Platform(box, hitBox),
      vx_(vx) {
}
PlatformMovable::PlatformMovable(const RectangleF& box, float vx)
    : PlatformMovable(box, RectangleF(0, 0, box.w, box.h), vx) {
}

void PlatformMovable::update(unsigned deltaTime, Window* win) {
    if (box_.x + box_.w >= win->get_width()) {
        direction_ = mDirection::left;
    }
    else if (box_.x <= 0) {
        direction_ = mDirection::right;
    }

    box_.x += direction_ * vx_ * deltaTime;
}

void PlatformMovable::draw(Window* win, const PointF& offset) const {
    win->draw_img(sprite::GAMETILES_FILE,
                  Rectangle(box_.x + offset.x, box_.y + offset.y, box_.w, box_.h),
                  sprite::platform[sprite::Platform::MOVABLE]);
}

GameObject::CollisionType PlatformMovable::collide(GameObject* col, Window* win) {
    return collideType_;
}