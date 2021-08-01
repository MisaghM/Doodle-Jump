#ifndef SPRING_NORMAL_HPP_INCLUDE
#define SPRING_NORMAL_HPP_INCLUDE

#include "../spritesheet.hpp"
#include "item.hpp"

class Window;

class Spring : public Item {
public:
    using Item::Item;

    void update(unsigned deltaTime, Window* win) override;
    void draw(Window* win, const PointF& offset = {0, 0}) const override;
    CollisionType collide(GameObject* col, Window* win) override;

private:
    static CollisionType collideType_;

    enum class State {
        base,
        sprung
    } state_ = State::base;
    sprite::Item currSprite_ = sprite::Item::SPRING;
};

#endif //SPRING_NORMAL_HPP_INCLUDE