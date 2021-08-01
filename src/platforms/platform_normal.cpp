#include "platform_normal.hpp"

#include "../RSDL/rsdl.hpp"
#include "../spritesheet.hpp"

GameObject::CollisionType PlatformNormal::collideType_ = GameObject::CollisionType::pNormal;

void PlatformNormal::update(unsigned deltaTime, Window* win) {}

void PlatformNormal::draw(Window* win, const PointF& offset) const {
    win->draw_img(sprite::GAMETILES_FILE,
                  Rectangle(box_.x + offset.x, box_.y + offset.y, box_.w, box_.h),
                  sprite::platform[sprite::Platform::NORMAL]);
}

GameObject::CollisionType PlatformNormal::collide(GameObject* col, Window* win) {
    return collideType_;
}