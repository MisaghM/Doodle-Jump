#ifndef MENU_UFO_HPP_INCLUDE
#define MENU_UFO_HPP_INCLUDE

#include <string>

#include "game_object.hpp"

class Window;

class MenuUfo : public GameObject {
public:
    MenuUfo(const RectangleF& box, const RectangleF& hitBox);
    MenuUfo(const RectangleF& box);

    void update(unsigned deltaTime, Window* win) override;
    void draw(Window* win, const PointF& offset = {0, 0}) const override;
    CollisionType collide(GameObject* col, Window* win) override;

private:
    static CollisionType collideType_;

    int getSpriteCut() const;
    float initialX_, initialY_;
    unsigned moveTimer_ = 0;
};

#endif //MENU_UFO_HPP_INCLUDE