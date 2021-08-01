#include "menu_ufo.hpp"

#include <cmath>

#include "RSDL/rsdl.hpp"
#include "spritesheet.hpp"

GameObject::CollisionType MenuUfo::collideType_ = GameObject::CollisionType::none;

MenuUfo::MenuUfo(const RectangleF& box, const RectangleF& hitBox)
    : GameObject(box, hitBox),
      initialX_(box.x),
      initialY_(box.y) {
}
MenuUfo::MenuUfo(const RectangleF& box)
    : MenuUfo(box, RectangleF(0, 0, box.w, box.h)) {
}

void MenuUfo::draw(Window* win, const PointF& offset) const {
    win->draw_img(sprite::GAMETILES_FILE,
                  Rectangle(box_.x + offset.x, box_.y + offset.y, box_.w, box_.h),
                  sprite::enemy[getSpriteCut()]);
}

void MenuUfo::update(unsigned deltaTime, Window* win) {
    moveTimer_ += deltaTime;
    //Lissajous Curves
    box_.x = 25 * sin((moveTimer_) * 0.001f) + initialX_;
    box_.y = 15 * sin((2 * moveTimer_) * 0.001f) + initialY_;
}

GameObject::CollisionType MenuUfo::collide(GameObject* col, Window* win) {
    return collideType_;
}

int MenuUfo::getSpriteCut() const {
    float num = abs(sin(moveTimer_ * 0.003f));
    if (num > 0.9 && num < 0.96) {
        return sprite::Enemy::UFO_ON;
    }
    else return sprite::Enemy::UFO_OFF;
}