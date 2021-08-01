#ifndef PLATFORM_NORMAL_HPP_INCLUDE
#define PLATFORM_NORMAL_HPP_INCLUDE

#include "platform.hpp"

class Window;

class PlatformNormal : public Platform {
public:
    using Platform::Platform;

    void update(unsigned deltaTime, Window* win) override;
    void draw(Window* win, const PointF& offset = {0, 0}) const override;
    CollisionType collide(GameObject* col, Window* win) override;

private:
    static CollisionType collideType_;
};

#endif //PLATFORM_NORMAL_HPP_INCLUDE