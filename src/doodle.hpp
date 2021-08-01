#ifndef DOODLE_HPP_INCLUDE
#define DOODLE_HPP_INCLUDE

#include <string>

#include "consts.hpp"
#include "game_object.hpp"
#include "spritesheet.hpp"

class InputManager;

class Doodle : public GameObject {
public:
    using GameObject::GameObject;

    void updateInputs(InputManager* inputMan);
    void update(unsigned deltaTime, Window* win) override;
    void draw(Window* win, const PointF& offset = {0, 0}) const override;
    CollisionType collide(GameObject* col, Window* win) override;

    bool isDead() const;

private:
    static CollisionType collideType_;

    void setSpriteState();
    void setHitbox();
    void die(Window* win);

    bool isOutOfScreenBottom(const Window* win) const;
    bool hasHitFromAbove(const GameObject* collided) const;

    using charState = sprite::Doodle;
    charState spriteState_ = charState::LEFT;

    enum class State {
        base,
        hit,
        dead
    } state_ = State::base;

    float vy_ = consts::DOODLE_VY;
    float vx_ = 0;
};

#endif //DOODLE_HPP_INCLUDE