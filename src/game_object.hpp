#ifndef GAME_OBJECT_HPP_INCLUDE
#define GAME_OBJECT_HPP_INCLUDE

#include "utils/point_f.hpp"
#include "utils/rectangle_f.hpp"

class Window;

/*
GameObject:
box    == {pos.x, pos.y, dim.w, dim.h}
hitBox == {deltaX, deltaY, w, h}
*/

class GameObject {
public:
    GameObject(const RectangleF& box, const RectangleF& hitBox);
    GameObject(const RectangleF& box);
    virtual ~GameObject();

    enum class CollisionType {
        pNormal,
        pBreakable,
        pMovable,
        enemyNormal,
        spring,
        none
    };

    virtual void update(unsigned deltaTime, Window* win) = 0;
    virtual void draw(Window* win, const PointF& offset = {0, 0}) const = 0;
    virtual CollisionType collide(GameObject* col, Window* win) = 0;

    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;

    int getHitboxDeltaX() const;
    int getHitboxDeltaY() const;
    int getHitboxWidth() const;
    int getHitboxHeight() const;

    void translateY(float deltaY);

protected:
    RectangleF box_;
    RectangleF hitBox_;
};

#endif //GAME_OBJECT_HPP_INCLUDE