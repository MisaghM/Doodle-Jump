#ifndef PLATFORM_MOVABLE_HPP_INCLUDE
#define PLATFORM_MOVABLE_HPP_INCLUDE

#include "platform.hpp"

class PlatformMovable : public Platform {
public:
    PlatformMovable(const RectangleF& box, const RectangleF& hitBox, float vx = 0.1f);
    PlatformMovable(const RectangleF& box, float vx = 0.1f);

    void update(unsigned deltaTime, Window* win) override;
    void draw(Window* win, const PointF& offset = {0, 0}) const override;
    CollisionType collide(GameObject* col, Window* win) override;

private:
    static CollisionType collideType_;

    enum mDirection {
        right = 1,
        left = -1
    } direction_ = mDirection::right;

    float vx_;
};

#endif //PLATFORM_MOVABLE_HPP_INCLUDE