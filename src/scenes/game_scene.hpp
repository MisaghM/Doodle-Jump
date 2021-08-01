#ifndef GAME_SCENE_HPP_INCLUDE
#define GAME_SCENE_HPP_INCLUDE

#include <string>
#include <vector>

#include "../consts.hpp"
#include "../doodle.hpp"
#include "../game_object.hpp"
#include "../sequence_manager.hpp"
#include "scene.hpp"

class Window;
class InputManager;

class GameScene : public Scene {
public:
    GameScene(InputManager* inputMan, const RectangleF& box);

    bool update(Window* win, unsigned deltaTime, System* sys) override;
    void draw(Window* win) override;

    int getScoreHeight() const;

private:
    Doodle doodle_;
    int height_ = 0;

    void moveDown(int translateY);
    void moveUp(int translateY);
    void removeObjectsBelow(const Window* win);
    void checkCollisions(Window* win);

    SequenceManager sm_;
    std::vector<GameObject*> chooseSeq();
    int currSeqHeight_ = 0;
    int currSeqTotalHeight_;
    int currSeqLastObjHeight_;
};

#endif //GAME_SCENE_HPP_INCLUDE