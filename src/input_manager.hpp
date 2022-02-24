#ifndef INPUT_MANAGER_HPP_INCLUDE
#define INPUT_MANAGER_HPP_INCLUDE

#include "RSDL/rsdl.hpp"
#include "consts.hpp"

struct InputKeys {
    enum type {
        right = 1 << 0,
        left = 1 << 1,
        pause = 1 << 2,
        any = 1 << 3
    };
};

struct InputMouse {
    enum type {
        Lclick = 1 << 0,
        Rclick = 1 << 1,
        Lrelease = 1 << 2,
        Rrelease = 1 << 3,
        hover = 1 << 4
    };
};

class InputManager {
public:
    InputManager() = default;

    void keyPressed(char key);
    void keyReleased(char key);
    void setMousePos(Point mousePos);
    void mouseHandle(InputMouse::type state);
    void reset();

    bool isKeyPressed(InputKeys::type key) const;
    bool didKeyPress(InputKeys::type key) const;
    bool didKeyRelease(InputKeys::type key) const;

    bool isMousePressed(InputMouse::type state) const;
    bool didMousePress(InputMouse::type state) const;
    bool didMouseRelease(InputMouse::type state) const;

    Point getMousePos() const;

private:
    Point mousePos_ = {0, 0};

    int keyInputs_ = 0;
    int keyPresses_ = 0;
    int keyReleases_ = 0;

    int mouseInputs_ = 0;
    int mouseReleases_ = 0;
    int mousePresses_ = 0;
};

#endif //INPUT_MANAGER_HPP_INCLUDE
