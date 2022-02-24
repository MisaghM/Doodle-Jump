#include "input_manager.hpp"

void InputManager::keyPressed(char key) {
    switch (key) {
    case consts::RIGHT:
        keyInputs_  |= InputKeys::right;
        keyPresses_ |= InputKeys::right;
        break;
    case consts::LEFT:
        keyInputs_  |= InputKeys::left;
        keyPresses_ |= InputKeys::left;
        break;
    case consts::PAUSE:
        keyInputs_  |= InputKeys::pause;
        keyPresses_ |= InputKeys::pause;
        break;
    default: break;
    }
}

void InputManager::keyReleased(char key) {
    switch (key) {
    case consts::RIGHT:
        keyInputs_ &= ~InputKeys::right;
        break;
    case consts::LEFT:
        keyInputs_ &= ~InputKeys::left;
        break;
    case consts::PAUSE:
        keyInputs_ &= ~InputKeys::pause;
        break;
    default: break;
    }
}

void InputManager::mouseHandle(InputMouse::type state) {
    switch (state) {
    case InputMouse::Lclick:
        mouseInputs_  |= InputMouse::Lclick;
        mousePresses_ |= InputMouse::Lclick;
        break;
    case InputMouse::Lrelease:
        mouseInputs_   &= ~InputMouse::Lclick;
        mouseReleases_ |= InputMouse::Lrelease;
        break;
    case InputMouse::Rclick:
        mouseInputs_  |= InputMouse::Rclick;
        mousePresses_ |= InputMouse::Rclick;
        break;
    case InputMouse::Rrelease:
        mouseInputs_   &= ~InputMouse::Rclick;
        mouseReleases_ |= InputMouse::Rrelease;
        break;
    default: break;
    }
}

void InputManager::reset() {
    mouseReleases_ = 0;
    mousePresses_ = 0;
    keyPresses_ = 0;
    keyReleases_ = 0;
}

void InputManager::setMousePos(Point mousePos) { mousePos_ = mousePos; }
Point InputManager::getMousePos() const { return mousePos_; }

bool InputManager::isKeyPressed(InputKeys::type key) const {
    if (key == InputKeys::any) return (keyInputs_ != 0);
    return (key & keyInputs_) != 0;
}

bool InputManager::didKeyPress(InputKeys::type key) const {
    if (key == InputKeys::any) return (keyPresses_ != 0);
    return (key & keyPresses_) != 0;
}

bool InputManager::didKeyRelease(InputKeys::type key) const {
    if (key == InputKeys::any) return (keyReleases_ != 0);
    return (key & keyReleases_) != 0;
}

bool InputManager::isMousePressed(InputMouse::type state) const {
    return (state & mouseInputs_) != 0;
}

bool InputManager::didMousePress(InputMouse::type state) const {
    return (state & mousePresses_) != 0;
}

bool InputManager::didMouseRelease(InputMouse::type state) const {
    return (state & mouseReleases_) != 0;
}