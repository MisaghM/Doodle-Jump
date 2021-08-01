#include "pause_scene.hpp"

#include "../RSDL/rsdl.hpp"
#include "../button.hpp"
#include "../game_object.hpp"
#include "../input_manager.hpp"
#include "../spritesheet.hpp"
#include "../system.hpp"
#include "../utils/calc.hpp"

PauseScene::PauseScene(InputManager* inputMan)
    : Scene(inputMan) {
    objs_.push_back(new Button(RectangleF(220, 460, sprite::button[sprite::Button::RESUME].w, sprite::button[sprite::Button::RESUME].h),
                               sprite::BUTTON_FILE,
                               sprite::button[sprite::Button::RESUME]));
}

void PauseScene::draw(Window* win) {
    win->draw_img(consts::PAUSE_COVER);
    for (GameObject* obj : objs_) {
        obj->draw(win);
    }
}

bool PauseScene::update(Window* win, unsigned deltaTime, System* sys) {
    if (inputMan_->didMouseRelease(InputMouse::Lrelease)) {
        if (collided(inputMan_->getMousePos(), objs_[0])) { //resume button
            sys->changeScene(System::SceneState::game);
            return true;
        }
    }
    if (inputMan_->didKeyPress(InputKeys::pause)) {
        sys->changeScene(System::SceneState::game);
        return true;
    }
    return true;
}