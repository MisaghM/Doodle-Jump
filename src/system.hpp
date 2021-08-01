#ifndef SYSTEM_HPP_INCLUDE
#define SYSTEM_HPP_INCLUDE

#include <vector>

#include "input_manager.hpp"
#include "scenes/game_scene.hpp"
#include "scenes/gameover_scene.hpp"
#include "scenes/menu_scene.hpp"
#include "scenes/pause_scene.hpp"
#include "scenes/scene.hpp"

class System {
public:
    System(Window* win);

    enum class SceneState {
        menu,
        game,
        pause,
        gameover
    };

    bool update();
    void draw();
    void changeScene(SceneState to);
    unsigned deltaTime = 0;

private:
    void makeGameScene();
    int recordHeight_ = 0;

    SceneState state_ = SceneState::menu;

    Window* win_;
    InputManager inputMan_;

    std::vector<Scene*> scenes_;
    MenuScene menuScene_;
    PauseScene pauseScene_;
    GameScene* gameScene_ = nullptr;
    GameoverScene* gameoverScene_ = nullptr;
};

#endif //SYSTEM_HPP_INCLUDE