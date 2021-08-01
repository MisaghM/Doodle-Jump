#ifndef PAUSE_SCENE_HPP_INCLUDE
#define PAUSE_SCENE_HPP_INCLUDE

#include "scene.hpp"

class PauseScene : public Scene {
public:
    PauseScene(InputManager* inputMan);

    bool update(Window* win, unsigned deltaTime, System* sys) override;
    void draw(Window* win) override;
};

#endif //PAUSE_SCENE_HPP_INCLUDE