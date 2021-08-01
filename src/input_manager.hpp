#ifndef INPUT_MANAGER_HPP_INCLUDE
#define INPUT_MANAGER_HPP_INCLUDE

#include "RSDL/rsdl.hpp"
#include "consts.hpp"

enum InputKeys {
    right,
    left,
    pause,
    any
};

enum InputMouse {
    Lclick,
    Rclick,
    Lrelease,
    Rrelease,
    hover
};

class InputManager {
public:
    InputManager() = default;

    void keyPressed(char key);
    void keyReleased(char key);
    void setMousePos(Point mousePos);
    void mouseHandle(InputMouse state);
    void reset();

    bool isKeyPressed(InputKeys key) const;
    bool didKeyPress(InputKeys key) const;
    bool didKeyRelease(InputKeys key) const;

    bool isMousePressed(InputMouse state) const;
    bool didMousePress(InputMouse state) const;
    bool didMouseRelease(InputMouse state) const;

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
