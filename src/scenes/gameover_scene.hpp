#ifndef GAMEOVER_SCENE_HPP_INCLUDE
#define GAMEOVER_SCENE_HPP_INCLUDE

#include <string>

#include "../consts.hpp"
#include "scene.hpp"

class InputManager;

class GameoverScene : public Scene {
public:
    GameoverScene(InputManager* inputMan, int height, int recordHeight);

    bool update(Window* win, unsigned deltaTime, System* sys) override;
    void draw(Window* win) override;

private:
    std::string height_;
    std::string recordHeight_;
    int imgY_ = 720;
};

#endif //GAMEOVER_SCENE_HPP_INCLUDE