#include "gameover_scene.hpp"

#include "../button.hpp"
#include "../game_object.hpp"
#include "../input_manager.hpp"
#include "../spritesheet.hpp"
#include "../system.hpp"
#include "../utils/calc.hpp"

GameoverScene::GameoverScene(InputManager* inputMan, int height, int recordHeight)
    : Scene(inputMan),
      height_(std::to_string(height)),
      recordHeight_(std::to_string(recordHeight)) {
    objs_.push_back(new Button(RectangleF(170, 390, sprite::button[sprite::Button::PLAYAGAIN].w, sprite::button[sprite::Button::PLAYAGAIN].h),
                               sprite::BUTTON_FILE,
                               sprite::button[sprite::Button::PLAYAGAIN]));
    objs_.push_back(new Button(RectangleF(250, 480, sprite::button[sprite::Button::MENU].w, sprite::button[sprite::Button::MENU].h),
                               sprite::BUTTON_FILE,
                               sprite::button[sprite::Button::MENU]));
}

bool GameoverScene::update(Window* win, unsigned deltaTime, System* sys) {
    if (imgY_ > 12) {
        imgY_ -= deltaTime;
    }
    else {
        imgY_ = 0;
        if (inputMan_->didMouseRelease(InputMouse::Lrelease)) {
            if (collided(inputMan_->getMousePos(), objs_[0])) { //play-again btn
                sys->changeScene(System::SceneState::game);
                return true;
            }
            else if (collided(inputMan_->getMousePos(), objs_[1])) { //menu btn
                sys->changeScene(System::SceneState::menu);
                return true;
            }
        }
    }

    return true;
}
void GameoverScene::draw(Window* win) {
    win->draw_img(consts::GAMEOVER_COVER, Rectangle(0, imgY_, win->get_width(), win->get_height()));
    if (imgY_ == 0) {
        for (GameObject* obj : objs_) {
            obj->draw(win);
        }
        win->show_text(height_, Point(270, 197), BLACK, consts::FONT);
        win->show_text(recordHeight_, Point(255, 240), BLACK, consts::FONT);
    }
}