#include "system.hpp"

#include "enemies/enemy_normal.hpp"
#include "items/spring.hpp"
#include "platforms/platform_breakable.hpp"
#include "platforms/platform_movable.hpp"
#include "platforms/platform_normal.hpp"
#include "spritesheet.hpp"

System::System(Window* win_)
    : win_(win_),
      menuScene_(&inputMan_),
      pauseScene_(&inputMan_) {
    scenes_.push_back(&menuScene_);
}

bool System::update() {
    inputMan_.reset();

    while (win_->has_pending_event()) {
        Event e = win_->poll_for_event();
        switch (e.get_type()) {
        case Event::EventType::QUIT: return false;
        case Event::EventType::KEY_PRESS:
            inputMan_.keyPressed(e.get_pressed_key());
            break;
        case Event::EventType::KEY_RELEASE:
            inputMan_.keyReleased(e.get_pressed_key());
            break;
        case Event::EventType::MMOTION:
            inputMan_.setMousePos(e.get_mouse_position());
            break;
        case Event::EventType::LCLICK:
            inputMan_.mouseHandle(InputMouse::Lclick);
            break;
        case Event::EventType::LRELEASE:
            inputMan_.mouseHandle(InputMouse::Lrelease);
            break;
        default: break;
        }
    }

    if (state_ == SceneState::gameover) scenes_[1]->update(win_, deltaTime, this);
    return scenes_.back()->update(win_, deltaTime, this);
}

void System::draw() {
    if (state_ == SceneState::pause ||
        state_ == SceneState::gameover) scenes_[1]->draw(win_);
    scenes_.back()->draw(win_);
}

void System::changeScene(SceneState to) {
    switch (state_) {
    case SceneState::menu:
        if (to == SceneState::game) {
            state_ = SceneState::game;
            makeGameScene();
            scenes_.push_back(gameScene_);
        }
        break;

    case SceneState::game:
        if (to == SceneState::pause) {
            state_ = SceneState::pause;
            scenes_.push_back(&pauseScene_);
        }
        else if (to == SceneState::gameover) {
            state_ = SceneState::gameover;

            int height = gameScene_->getScoreHeight();
            if (height > recordHeight_) recordHeight_ = height;

            gameoverScene_ = new GameoverScene(&inputMan_, height, recordHeight_);
            scenes_.push_back(gameoverScene_);
        }
        break;

    case SceneState::pause:
        if (to == SceneState::game) {
            state_ = SceneState::game;
            scenes_.pop_back();
        }
        break;

    case SceneState::gameover:
        if (to == SceneState::game) {
            state_ = SceneState::game;
            delete scenes_.back();
            scenes_.pop_back();
            delete scenes_.back();
            scenes_.pop_back();
            makeGameScene();
            scenes_.push_back(gameScene_);
        }
        else if (to == SceneState::menu) {
            state_ = SceneState::menu;
            delete scenes_.back();
            scenes_.pop_back();
            delete scenes_.back();
            scenes_.pop_back();
        }
        break;
    }
}

void System::makeGameScene() {
    int doodleWidth = sprite::doodle[sprite::Doodle::LEFT].w;
    int doodleHeight = sprite::doodle[sprite::Doodle::LEFT].h;
    gameScene_ = new GameScene(&inputMan_,
                               RectangleF(win_->get_width() / 2 - doodleWidth / 2, win_->get_height() - doodleHeight, doodleWidth, doodleHeight));
}