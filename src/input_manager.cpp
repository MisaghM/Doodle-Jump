#include "input_manager.hpp"

void InputManager::keyPressed(char key) {
    switch (key) {
    case consts::RIGHT:
        keyInputs_  |= 1 << InputKeys::right;
        keyPresses_ |= 1 << InputKeys::right;
        break;
    case consts::LEFT:
        keyInputs_  |= 1 << InputKeys::left;
        keyPresses_ |= 1 << InputKeys::left;
        break;
    case consts::PAUSE:
        keyInputs_  |= 1 << InputKeys::pause;
        keyPresses_ |= 1 << InputKeys::pause;
        break;
    default: break;
    }
}

void InputManager::keyReleased(char key) {
    switch (key) {
    case consts::RIGHT:
        keyInputs_ &= ~(1 << InputKeys::right);
        break;
    case consts::LEFT:
        keyInputs_ &= ~(1 << InputKeys::left);
        break;
    case consts::PAUSE:
        keyInputs_ &= ~(1 << InputKeys::pause);
        break;
    default: break;
    }
}

void InputManager::mouseHandle(InputMouse state) {
    switch (state) {
    case InputMouse::Lclick:
        mouseInputs_  |= 1 << InputMouse::Lclick;
        mousePresses_ |= 1 << InputMouse::Lclick;
        break;
    case InputMouse::Lrelease:
        mouseInputs_   &= ~(1 << InputMouse::Lclick);
        mouseReleases_ |= 1 << InputMouse::Lrelease;
        break;
    case InputMouse::Rclick:
        mouseInputs_  |= 1 << InputMouse::Rclick;
        mousePresses_ |= 1 << InputMouse::Rclick;
        break;
    case InputMouse::Rrelease:
        mouseInputs_   &= ~(1 << InputMouse::Rclick);
        mouseReleases_ |= 1 << InputMouse::Rrelease;
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

bool InputManager::isKeyPressed(InputKeys key) const {
    if (key == InputKeys::any) return (keyInputs_ != 0);
    return (((1 << key) & keyInputs_) != 0);
}

bool InputManager::didKeyPress(InputKeys key) const {
    if (key == InputKeys::any) return (keyPresses_ != 0);
    return (((1 << key) & keyPresses_) != 0);
}

bool InputManager::didKeyRelease(InputKeys key) const {
    if (key == InputKeys::any) return (keyReleases_ != 0);
    return (((1 << key) & keyReleases_) != 0);
}

bool InputManager::isMousePressed(InputMouse state) const {
    return (((1 << state) & mouseInputs_) != 0);
}

bool InputManager::didMousePress(InputMouse state) const {
    return (((1 << state) & mousePresses_) != 0);
}

bool InputManager::didMouseRelease(InputMouse state) const {
    return (((1 << state) & mouseReleases_) != 0);
}