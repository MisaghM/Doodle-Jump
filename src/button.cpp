#include "button.hpp"

#include "RSDL/rsdl.hpp"

GameObject::CollisionType Button::collideType_ = GameObject::CollisionType::none;

Button::Button(const RectangleF& box, const RectangleF& hitBox, const std::string& img, const Rectangle& spriteCut)
    : GameObject(box, hitBox),
      img_(img),
      spriteIsCut_(true),
      spriteCut_(spriteCut) {
}
Button::Button(const RectangleF& box, const std::string& img, const Rectangle& spriteCut)
    : Button(box, RectangleF(0, 0, box.w, box.h), img, spriteCut) {
}
Button::Button(const RectangleF& box, const RectangleF& hitBox, const std::string& img)
    : GameObject(box, hitBox),
      img_(img),
      spriteIsCut_(false) {
}
Button::Button(const RectangleF& box, const std::string& img)
    : Button(box, RectangleF(0, 0, box.w, box.h), img) {
}

void Button::draw(Window* win, const PointF& offset) const {
    if (spriteIsCut_) {
        win->draw_img(img_, Rectangle(box_.x + offset.x, box_.y + offset.y, box_.w, box_.h), spriteCut_);
    }
    else {
        win->draw_img(img_, Rectangle(box_.x + offset.x, box_.y + offset.y, box_.w, box_.h));
    }
}

void Button::update(unsigned deltaTime, Window* win) {}

GameObject::CollisionType Button::collide(GameObject* col, Window* win) {
    return collideType_;
}