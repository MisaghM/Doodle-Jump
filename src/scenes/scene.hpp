#ifndef SCENE_HPP_INCLUDE
#define SCENE_HPP_INCLUDE

#include <vector>

class Window;
class InputManager;
class System;
class GameObject;

class Scene {
public:
    Scene(InputManager* inputMan);
    virtual ~Scene();

    virtual bool update(Window* win, unsigned deltaTime, System* sys);
    virtual void draw(Window* win);

protected:
    InputManager* inputMan_;
    std::vector<GameObject*> objs_;
};

#endif //SCENE_HPP_INCLUDE